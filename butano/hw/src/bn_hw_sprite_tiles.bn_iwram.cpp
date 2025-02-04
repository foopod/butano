/*
 * Copyright (c) 2020-2021 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#include "../include/bn_hw_sprite_tiles.h"

#include "bn_tile.h"
#include "../include/bn_hw_memory.h"

namespace bn::hw::sprite_tiles
{

void plot_tiles(int width, const tile* source_tiles_ptr, int source_height, int source_y, int destination_y,
                tile* destination_tiles_ptr)
{
    // From TONC:

    auto srcD = reinterpret_cast<const unsigned*>(source_tiles_ptr + source_y / 8);
    auto dstD = reinterpret_cast<unsigned*>(destination_tiles_ptr + destination_y / 8);
    int dstX0 = destination_y & 7;

    if(! dstX0)
    {
        // Simple cases : aligned pixels:

        for(int ix = 0; ix < width; ix += 8)
        {
            hw::memory::copy_words(srcD, 8, dstD);
            srcD += source_height;
            dstD += 8;
        }
    }
    else
    {
        // Hideous cases : srcX0 != dstX0:

        auto lmask = [](int left) {
            return 0xFFFFFFFFU << (((left) & 7) * 4);
        };

        auto rmask = [](int right) {
            return 0xFFFFFFFFU >> ((-(right) & 7) * 4);
        };

        unsigned lsl = 4 * unsigned(dstX0);
        unsigned lsr = 32 - lsl;
        unsigned mask = lmask(0);

        for(int ix = width; ix > 0; ix -= 8)
        {
            if(ix < 8)
            {
                mask &= rmask(ix);
            }

            unsigned* dstL = dstD;
            dstD += 8;

            const unsigned* srcL = srcD;
            srcD += source_height;

            for(int iy = 0; iy < 8; ++iy)
            {
                unsigned px = *srcL++ & mask;

                // Write to left tile:
                dstL[0] = (dstL[0] &~ (mask << lsl)) | (px << lsl);

                // Write to right tile:
                dstL[8] = (dstL[8] &~ (mask >> lsr)) | (px >> lsr);

                ++dstL;
            }

            mask = 0xFFFFFFFF;
        }
    }
}

}
