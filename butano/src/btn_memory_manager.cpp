#include "btn_memory_manager.h"

#include "btn_list.h"
#include "btn_vector.h"
#include "btn_config_memory.h"
#include "../hw/include/btn_hw_memory.h"

#include "btn_log.h"

namespace btn::memory_manager
{

namespace
{
    static_assert(BTN_CFG_MEMORY_MAX_EWRAM_ALLOC_ITEMS > 0);


    constexpr const int max_items = BTN_CFG_MEMORY_MAX_EWRAM_ALLOC_ITEMS;


    class item_type
    {

    public:
        char* data = nullptr;
        int size: 24 = 0;
        bool used = false;
    };


    using items_list = list<item_type, max_items>;
    using items_iterator = items_list::iterator;

    static_assert(sizeof(items_iterator) == sizeof(int));
    static_assert(alignof(items_iterator) == alignof(int));


    class static_data
    {

    public:
        items_list items;
        vector<items_iterator, max_items> free_items;
        int total_bytes_count = 0;
        int free_bytes_count = 0;
    };

    BTN_DATA_EWRAM static_data data;

    constexpr const auto lower_bound_comparator = [](const items_iterator& items_it, int size)
    {
        return items_it->size < size;
    };

    constexpr const auto upper_bound_comparator = [](int size, const items_iterator& items_it)
    {
        return size < items_it->size;
    };

    void _insert_free_item(items_iterator items_it)
    {
        auto free_items_it = upper_bound(data.free_items.begin(), data.free_items.end(), items_it->size,
                                         upper_bound_comparator);
        data.free_items.insert(free_items_it, items_it);
    }

    void _erase_free_item(items_iterator items_it)
    {
        auto free_items_end = data.free_items.end();
        auto free_items_it = lower_bound(data.free_items.begin(), free_items_end, items_it->size,
                                         lower_bound_comparator);
        BTN_ASSERT(free_items_it != free_items_end, "Free item not found: ", static_cast<void*>(items_it->data));

        while(*free_items_it != items_it)
        {
            ++free_items_it;
        }

        data.free_items.erase(free_items_it);
    }

    [[nodiscard]] void* _create_item(items_iterator items_it, int bytes)
    {
        item_type& item = *items_it;
        BTN_ASSERT(! item.used, "Item is not free: ", item.size);

        item.used = true;

        if(int new_item_size = item.size - bytes)
        {
            BTN_ASSERT(! data.items.full(), "No more items allowed");

            item_type new_item;
            new_item.data = item.data;
            new_item.size = new_item_size;

            items_iterator new_items_it = data.items.insert(items_it, new_item);
            _insert_free_item(new_items_it);
            item.data += new_item_size;
            item.size = bytes;
        }

        auto items_it_ptr = reinterpret_cast<items_iterator*>(item.data);
        *items_it_ptr = items_it;
        data.free_bytes_count -= bytes;
        return items_it_ptr + 1;
    }
}

void init()
{
    char* start = hw::memory::ewram_heap_start();
    char* end = hw::memory::ewram_heap_end();
    data.total_bytes_count = end - start;
    BTN_ASSERT(data.total_bytes_count >= 0, "Invalid heap size: ",
               static_cast<void*>(start), " - ", static_cast<void*>(end));

    item_type new_item;
    new_item.data = start;
    new_item.size = data.total_bytes_count;
    data.items.push_front(new_item);
    data.free_items.push_back(data.items.begin());
    data.free_bytes_count = data.total_bytes_count;
}

void* ewram_alloc(int bytes)
{
    BTN_ASSERT(bytes >= 0, "Invalid bytes: ", bytes);

    int alignment_bytes = sizeof(int);

    if(int extra_bytes = bytes % alignment_bytes)
    {
        bytes += alignment_bytes - extra_bytes;
    }

    bytes += sizeof(items_iterator);

    if(bytes <= data.free_bytes_count)
    {
        auto free_items_end = data.free_items.end();
        auto free_items_it = lower_bound(data.free_items.begin(), free_items_end, bytes, lower_bound_comparator);

        if(free_items_it != free_items_end)
        {
            auto items_it = *free_items_it;
            data.free_items.erase(free_items_it);
            return _create_item(items_it, bytes);
        }
    }

    return nullptr;
}

void ewram_free(void* ptr)
{
    if(ptr)
    {
        auto items_it_ptr = reinterpret_cast<items_iterator*>(ptr) - 1;
        items_iterator items_it = *items_it_ptr;
        item_type& item = *items_it;
        BTN_ASSERT(item.used, "Item is not used: ", item.size);

        item.used = false;
        data.free_bytes_count += item.size;

        if(items_it != data.items.begin())
        {
            items_iterator previous_items_it = items_it;
            --previous_items_it;

            item_type& previous_item = *previous_items_it;

            if(! previous_item.used && previous_item.data + previous_item.size == item.data)
            {
                item.data = previous_item.data;
                item.size += previous_item.size;
                _erase_free_item(previous_items_it);
                data.items.erase(previous_items_it);
            }
        }

        items_iterator next_items_it = items_it;
        ++next_items_it;

        if(next_items_it != data.items.end())
        {
            item_type& next_item = *next_items_it;

            if(! next_item.used && item.data + item.size == next_item.data)
            {
                item.size += next_item.size;
                _erase_free_item(next_items_it);
                data.items.erase(next_items_it);
            }
        }

        _insert_free_item(items_it);
    }
}

int used_alloc_ewram()
{
    return data.total_bytes_count - data.free_bytes_count;
}

int available_alloc_ewram()
{
    return data.free_bytes_count;
}

}
