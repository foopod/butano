/*
 * Copyright (c) 2020-2021 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BF_CONSTANTS_H
#define BF_CONSTANTS_H

#include "bn_fixed.h"
#include "bn_display.h"

#ifndef BF_CFG_ENEMIES_GRID_LOG_ENABLED
    #define BF_CFG_ENEMIES_GRID_LOG_ENABLED false
#endif

namespace bf::constants
{
    constexpr const int max_hero_bullets = 32;
    constexpr const int max_hero_bombs = 4;
    constexpr const int max_enemies = 48;
    constexpr const int max_enemy_bullets = 48;
    constexpr const int max_gems = 8;
    constexpr const int max_object_messages = max_gems;
    constexpr const int max_enemy_size = 64;
    constexpr const int play_width = 72;
    constexpr const int play_height = (bn::display::height() - 42) / 2;
    constexpr const int view_width = (play_width * 2) + (max_enemy_size / 2);
    constexpr const int view_height = (bn::display::height() + max_enemy_size) / 2;
    constexpr const int camera_width = 32;
    constexpr const int hero_bullet_levels = 9;
    constexpr const int hero_shield_z_order = -2;
    constexpr const int enemy_bullets_z_order = -1;
    constexpr const int objects_z_order = 1;
    constexpr const int hero_bullets_z_order = 2;
    constexpr const int enemy_explosions_z_order = 3;
    constexpr const int enemies_z_order = 4;
    constexpr const int gems_z_order = 5;
    constexpr const int object_messages_z_order = 6;
    constexpr const int hero_shadows_z_order = 7;
    constexpr const int intro_sprites_z_order = 8;
    constexpr const int footprint_z_order = 9;
    constexpr const int hero_bullets_sound_priority = -2;
    constexpr const int enemies_sound_priority = -1;
    constexpr const int enemies_grid_size = 16;
    constexpr const int max_enemies_in_grid = 384;
    constexpr const int enemies_invencible_frames = 30;
    constexpr const int reserved_sprite_affine_mats = 3;
    constexpr const bn::fixed background_speed = 0.5;
    constexpr const int object_flash_frames = 16;
}

#endif
