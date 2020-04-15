#include "btn_sorted_sprites.h"

#include "btn_pool.h"
#include "btn_vector.h"
#include "btn_config_sprites.h"
#include "btn_sprites_manager_item.h"
#include "../hw/include/btn_hw_bgs.h"

namespace btn::sorted_sprites
{

namespace
{
    static_assert(BTN_CFG_SPRITES_MAX_SORT_LAYERS >= hw::bgs::count() &&
                  BTN_CFG_SPRITES_MAX_SORT_LAYERS <= BTN_CFG_SPRITES_MAX_ITEMS);

    class static_data
    {

    public:
        pool<layer, BTN_CFG_SPRITES_MAX_SORT_LAYERS> layer_pool;
        vector<layer*, BTN_CFG_SPRITES_MAX_SORT_LAYERS> layer_ptrs;
        int items_count = 0;
    };

    BTN_DATA_EWRAM static_data data;
}

int items_count()
{
    return data.items_count;
}

layers_type& layers()
{
    return data.layer_ptrs;
}

void insert(sprites_manager_item& item)
{
    layers_type& layers = data.layer_ptrs;
    unsigned sort_key = item.sort_key;
    layer new_layer(sort_key);
    auto layers_end = layers.end();
    auto layers_it = lower_bound(layers.begin(), layers_end, &new_layer, [](const layer* a, const layer* b) {
        return a->sort_key() < b->sort_key();
    });

    if(layers_it == layers_end)
    {
        BTN_ASSERT(! layers.full(), "No more sprite sort layers available");

        layer& pool_layer = data.layer_pool.create(sort_key);
        layers.push_back(&pool_layer);
        layers_it = layers_end;
    }
    else if(sort_key != (*layers_it)->sort_key())
    {
        BTN_ASSERT(! layers.full(), "No more sprite sort layers available");

        layer& pool_layer = data.layer_pool.create(sort_key);
        layers_it = layers.insert(layers_it, &pool_layer);
    }

    layer* layer = *layers_it;
    layer->push_front(item);
    ++data.items_count;
}

void erase(sprites_manager_item& item)
{
    layers_type& layers = data.layer_ptrs;
    unsigned sort_key = item.sort_key;
    layer new_list(sort_key);
    auto layers_end = layers.end();
    auto layers_it = lower_bound(layers.begin(), layers_end, &new_list, [](const layer* a, const layer* b) {
        return a->sort_key() < b->sort_key();
    });

    BTN_ASSERT(layers_it != layers_end, "Sprite sort key not found: ", sort_key);
    BTN_ASSERT(sort_key == (*layers_it)->sort_key(), "Sprite sort key not found: ", sort_key);

    layer* layer = *layers_it;
    layer->erase(item);
    --data.items_count;

    if(layer->empty())
    {
        layers.erase(layers_it);
        data.layer_pool.destroy(*layer);
    }
}

}
