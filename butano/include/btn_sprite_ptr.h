/*
 * Copyright (c) 2020 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

#ifndef BTN_SPRITE_PTR_H
#define BTN_SPRITE_PTR_H

#include "btn_utility.h"
#include "btn_fixed_fwd.h"
#include "btn_functional.h"
#include "btn_optional_fwd.h"

namespace btn
{

class size;
class camera_ptr;
class fixed_point;
class sprite_item;
class sprite_builder;
class regular_bg_ptr;
class sprite_tiles_ptr;
class sprite_shape_size;
class sprite_tiles_item;
class sprite_palette_ptr;
class sprite_palette_item;
class sprite_affine_mat_ptr;
class sprite_first_attributes;
class sprite_third_attributes;
class sprite_affine_second_attributes;
class sprite_regular_second_attributes;
enum class sprite_double_size_mode;

/**
 * @brief Smart pointer that retains shared ownership of a sprite.
 *
 * Several sprite_ptr objects may own the same sprite.
 *
 * The sprite is released when the last remaining sprite_ptr owning it is destroyed.
 *
 * @ingroup sprite
 */
class sprite_ptr
{

public:
    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(fixed x, fixed y, const sprite_item& item);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @param graphics_index Index of the tile set to reference in item.tiles_item().
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(fixed x, fixed y, const sprite_item& item, int graphics_index);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param position Position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(const fixed_point& position, const sprite_item& item);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param position Position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @param graphics_index Index of the tile set to reference in item.tiles_item().
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(const fixed_point& position, const sprite_item& item, int graphics_index);

    /**
     * @brief Creates a sprite_ptr.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param shape_size Shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(fixed x, fixed y, const sprite_shape_size& shape_size,
                                           sprite_tiles_ptr tiles, sprite_palette_ptr palette);

    /**
     * @brief Creates a sprite_ptr.
     * @param position Position of the sprite.
     * @param shape_size Shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(const fixed_point& position, const sprite_shape_size& shape_size,
                                           sprite_tiles_ptr tiles, sprite_palette_ptr palette);

    /**
     * @brief Creates a sprite_ptr from a sprite_builder reference.
     * @param builder sprite_builder reference.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(const sprite_builder& builder);

    /**
     * @brief Creates a sprite_ptr from a moved sprite_builder.
     * @param builder sprite_builder to move.
     * @return The requested sprite_ptr.
     */
    [[nodiscard]] static sprite_ptr create(sprite_builder&& builder);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(fixed x, fixed y, const sprite_item& item);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @param graphics_index Index of the tile set to reference in item.tiles_item().
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(fixed x, fixed y, const sprite_item& item,
                                                              int graphics_index);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param position Position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(const fixed_point& position, const sprite_item& item);

    /**
     * @brief Creates a sprite_ptr from the given sprite_item.
     * @param position Position of the sprite.
     * @param item sprite_item containing the required information to generate the sprite.
     * @param graphics_index Index of the tile set to reference in item.tiles_item().
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(const fixed_point& position, const sprite_item& item,
                                                              int graphics_index);

    /**
     * @brief Creates a sprite_ptr.
     * @param x Horizontal position of the sprite.
     * @param y Vertical position of the sprite.
     * @param shape_size Shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(
            fixed x, fixed y, const sprite_shape_size& shape_size, sprite_tiles_ptr tiles, sprite_palette_ptr palette);

    /**
     * @brief Creates a sprite_ptr.
     * @param position Position of the sprite.
     * @param shape_size Shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(
            const fixed_point& position, const sprite_shape_size& shape_size, sprite_tiles_ptr tiles,
            sprite_palette_ptr palette);

    /**
     * @brief Creates a sprite_ptr from a sprite_builder reference.
     * @param builder sprite_builder reference.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(const sprite_builder& builder);

    /**
     * @brief Creates a sprite_ptr from a moved sprite_builder.
     * @param builder sprite_builder to move.
     * @return The requested sprite_ptr if it can be allocated; <b>nullopt</b> otherwise.
     */
    [[nodiscard]] static optional<sprite_ptr> create_optional(sprite_builder&& builder);

    /**
     * @brief Copy constructor.
     * @param other sprite_ptr to copy.
     */
    sprite_ptr(const sprite_ptr& other);

    /**
     * @brief Copy assignment operator.
     * @param other sprite_ptr to copy.
     * @return Reference to this.
     */
    sprite_ptr& operator=(const sprite_ptr& other);

    /**
     * @brief Move constructor.
     * @param other sprite_ptr to move.
     */
    sprite_ptr(sprite_ptr&& other) noexcept :
        sprite_ptr(other._handle)
    {
        other._handle = nullptr;
    }

    /**
     * @brief Move assignment operator.
     * @param other sprite_ptr to move.
     * @return Reference to this.
     */
    sprite_ptr& operator=(sprite_ptr&& other) noexcept
    {
        btn::swap(_handle, other._handle);
        return *this;
    }

    /**
     * @brief Release the referenced sprite if no more sprite_ptr objects reference to it.
     */
    ~sprite_ptr()
    {
        if(_handle)
        {
            _destroy();
        }
    }

    /**
     * @brief Returns the shape and size of the sprite.
     */
    [[nodiscard]] sprite_shape_size shape_size() const;

    /**
     * @brief Returns the size in pixels of the sprite.
     */
    [[nodiscard]] size dimensions() const;

    /**
     * @brief Returns the tiles used by this sprite.
     */
    [[nodiscard]] const sprite_tiles_ptr& tiles() const;

    /**
     * @brief Sets the tiles used by this sprite.
     * @param tiles Smart pointer to a sprite tile set to copy.
     *
     * It must be compatible with the current color palette, shape and size of the sprite.
     */
    void set_tiles(const sprite_tiles_ptr& tiles);

    /**
     * @brief Sets the tiles used by this sprite.
     * @param tiles Smart pointer to a sprite tile set to move.
     *
     * It must be compatible with the current color palette, shape and size of the sprite.
     */
    void set_tiles(sprite_tiles_ptr&& tiles);

    /**
     * @brief Sets the tiles, the shape and size of the sprite.
     * @param shape_size New shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set to copy.
     *
     * It must be compatible with the current color palette of the sprite.
     */
    void set_tiles(const sprite_shape_size& shape_size, const sprite_tiles_ptr& tiles);

    /**
     * @brief Sets the tiles, the shape and size of the sprite.
     * @param shape_size New shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set to move.
     *
     * It must be compatible with the current color palette of the sprite.
     */
    void set_tiles(const sprite_shape_size& shape_size, sprite_tiles_ptr&& tiles);

    /**
     * @brief Replaces the tiles used by this sprite with a new tile set created with the given sprite_tiles_item.
     *
     * Before creating a new sprite tile set, the sprite_tiles_ptr used by this sprite is removed,
     * so VRAM usage is reduced.
     *
     * The new sprite tiles must be compatible with the current color palette, shape and size of the sprite.
     *
     * @param tiles_item It creates the new sprite tiles to use by this sprite.
     */
    void set_tiles(const sprite_tiles_item& tiles_item);

    /**
     * @brief Replaces the tiles used by this sprite with a new tile set created with the given sprite_tiles_item.
     *
     * Before creating a new sprite tile set, the sprite_tiles_ptr used by this sprite is removed,
     * so VRAM usage is reduced.
     *
     * The new sprite tiles must be compatible with the current color palette, shape and size of the sprite.
     *
     * @param tiles_item It creates the new sprite tiles to use by this sprite.
     * @param graphics_index Index of the tile set to reference in tiles_item.
     */
    void set_tiles(const sprite_tiles_item& tiles_item, int graphics_index);

    /**
     * @brief Replaces the tiles used by this sprite with a new tile set created with the given sprite_tiles_item,
     * changing also the shape and size of the sprite.
     *
     * Before creating a new sprite tile set, the sprite_tiles_ptr used by this sprite is removed,
     * so VRAM usage is reduced.
     *
     * The new sprite tiles must be compatible with the current color palette of the sprite.
     *
     * @param tiles_item It creates the new sprite tiles to use by this sprite.
     * @param shape_size New shape and size of the sprite.
     */
    void set_tiles(const sprite_tiles_item& tiles_item, const sprite_shape_size& shape_size);

    /**
     * @brief Replaces the tiles used by this sprite with a new tile set created with the given sprite_tiles_item,
     * changing also the shape and size of the sprite.
     *
     * Before creating a new sprite tile set, the sprite_tiles_ptr used by this sprite is removed,
     * so VRAM usage is reduced.
     *
     * The new sprite tiles must be compatible with the current color palette of the sprite.
     *
     * @param tiles_item It creates the new sprite tiles to use by this sprite.
     * @param shape_size New shape and size of the sprite.
     * @param graphics_index Index of the tile set to reference in tiles_item.
     */
    void set_tiles(const sprite_tiles_item& tiles_item, const sprite_shape_size& shape_size, int graphics_index);

    /**
     * @brief Returns the color palette used by this sprite.
     */
    [[nodiscard]] const sprite_palette_ptr& palette() const;

    /**
     * @brief Sets the color palette to use by this sprite.
     * @param palette Smart pointer to a sprite color palette to copy.
     *
     * It must be compatible with the current tiles of the sprite.
     */
    void set_palette(const sprite_palette_ptr& palette);

    /**
     * @brief Sets the color palette to use by this sprite.
     * @param palette Smart pointer to a sprite color palette to move.
     *
     * It must be compatible with the current tiles of the sprite.
     */
    void set_palette(sprite_palette_ptr&& palette);

    /**
     * @brief Replaces the color palette used by this sprite with a new one created with the given sprite_palette_item.
     *
     * Before creating a new color palette, the sprite_palette_ptr used by this sprite is removed,
     * so VRAM usage is reduced.
     *
     * The new color palette must be compatible with the current tiles of the sprite.
     *
     * @param palette_item It creates the new color palette to use by this sprite.
     */
    void set_palette(const sprite_palette_item& palette_item);

    /**
     * @brief Sets the tiles and the color palette to use by this sprite.
     *
     * The given parameters must be compatible with the current shape and size of the sprite.
     *
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     */
    void set_tiles_and_palette(sprite_tiles_ptr tiles, sprite_palette_ptr palette);

    /**
     * @brief Sets the tiles, the color palette, the shape and size to use by this sprite.
     * @param shape_size New shape and size of the sprite.
     * @param tiles Smart pointer to a sprite tile set.
     * @param palette Smart pointer to a sprite color palette.
     */
    void set_tiles_and_palette(const sprite_shape_size& shape_size, sprite_tiles_ptr tiles, sprite_palette_ptr palette);

    /**
     * @brief Replaces the tiles, the color palette, the shape and size used by this sprite with
     * the created with the given sprite_item.
     *
     * Before creating new resources, the resources used by this sprite are removed, so VRAM usage is reduced.
     *
     * @param item It creates the new resources to use by this sprite.
     */
    void set_item(const sprite_item& item);

    /**
     * @brief Replaces the tiles, the color palette, the shape and size used by this sprite with
     * the created with the given sprite_item.
     *
     * Before creating new resources, the resources used by this sprite are removed, so VRAM usage is reduced.
     *
     * @param item It creates the new resources to use by this sprite.
     * @param graphics_index Index of the tile set to reference in item.tiles_item().
     */
    void set_item(const sprite_item& item, int graphics_index);

    /**
     * @brief Returns the horizontal position of the sprite (relative to its camera, if it has one).
     */
    [[nodiscard]] fixed x() const;

    /**
     * @brief Returns the vertical position of the sprite (relative to its camera, if it has one).
     */
    [[nodiscard]] fixed y() const;

    /**
     * @brief Returns the position of the sprite (relative to its camera, if it has one).
     */
    [[nodiscard]] const fixed_point& position() const;

    /**
     * @brief Sets the horizontal position of the sprite (relative to its camera, if it has one).
     */
    void set_x(fixed x);

    /**
     * @brief Sets the vertical position of the sprite (relative to its camera, if it has one).
     */
    void set_y(fixed y);

    /**
     * @brief Sets the position of the sprite (relative to its camera, if it has one).
     * @param x Horizontal position of the sprite (relative to its camera, if it has one).
     * @param y Vertical position of the sprite (relative to its camera, if it has one).
     */
    void set_position(fixed x, fixed y);

    /**
     * @brief Sets the position of the sprite (relative to its camera, if it has one).
     */
    void set_position(const fixed_point& position);

    /**
     * @brief Returns the rotation angle of the sprite in degrees.
     */
    [[nodiscard]] fixed rotation_angle() const;

    /**
     * @brief Sets the rotation angle of the sprite in degrees.
     * @param rotation_angle New rotation angle in degrees, in the range [0..360].
     *
     * If the rotation angle is != 0 and the sprite doesn't have an attached affine mat,
     * a new one with the given rotation angle it attached to the sprite.
     */
    void set_rotation_angle(fixed rotation_angle);

    /**
     * @brief Returns the horizontal scale of the sprite.
     */
    [[nodiscard]] fixed horizontal_scale() const;

    /**
     * @brief Sets the horizontal scale of the sprite.
     *
     * If the horizontal scale is != 1 and the sprite doesn't have an attached affine mat,
     * a new one with the given horizontal scale it attached to the sprite.
     */
    void set_horizontal_scale(fixed horizontal_scale);

    /**
     * @brief Returns the vertical scale of the sprite.
     */
    [[nodiscard]] fixed vertical_scale() const;

    /**
     * @brief Sets the vertical scale of the sprite.
     *
     * If the vertical scale is != 1 and the sprite doesn't have an attached affine mat,
     * a new one with the given vertical scale it attached to the sprite.
     */
    void set_vertical_scale(fixed vertical_scale);

    /**
     * @brief Sets the scale of the sprite.
     *
     * If the scale is != 1 and the sprite doesn't have an attached affine mat,
     * a new one with the given scale it attached to the sprite.
     */
    void set_scale(fixed scale);

    /**
     * @brief Sets the scale of the sprite.
     * @param horizontal_scale New horizontal scale.
     * @param vertical_scale New vertical scale.
     *
     * If the scale is != 1 and the sprite doesn't have an attached affine mat,
     * a new one with the given scale it attached to the sprite.
     */
    void set_scale(fixed horizontal_scale, fixed vertical_scale);

    /**
     * @brief Returns the priority relative to backgrounds.
     *
     * Higher priorities are drawn first (and therefore can be covered by later sprites and backgrounds).
     * Sprites cover backgrounds of the same priority.
     */
    [[nodiscard]] int bg_priority() const;

    /**
     * @brief Sets the priority relative to backgrounds.
     *
     * Higher priorities are drawn first (and therefore can be covered by later sprites and backgrounds).
     * Sprites cover backgrounds of the same priority.
     *
     * @param bg_priority Priority relative to backgrounds in the range [0..3].
     */
    void set_bg_priority(int bg_priority);

    /**
     * @brief Returns the priority relative to other sprites.
     *
     * Higher priorities are drawn first (and therefore can be covered by later sprites).
     *
     * Sprites are grouped in layers depending of their z order, so to reduce memory usage and improve performance,
     * please use as less unique z orders as possible.
     */
    [[nodiscard]] int z_order() const;

    /**
     * @brief Sets the priority relative to other sprites.
     *
     * Higher priorities are drawn first (and therefore can be covered by later sprites).
     *
     * Sprites are grouped in layers depending of their z order, so to reduce memory usage and improve performance,
     * please use as less unique z orders as possible.
     *
     * @param z_order Priority relative to other sprites in the range [-32767..32767].
     */
    void set_z_order(int z_order);

    /**
     * @brief Indicates if this sprite is drawn above the given one if they differ in their bg_priority or z_order.
     * Otherwise, it returns <b>nullopt</b>.
     */
    [[nodiscard]] optional<bool> above(const sprite_ptr& other) const;

    /**
     * @brief Indicates if this sprite is drawn above the given regular background.
     */
    [[nodiscard]] bool above(const regular_bg_ptr& bg_ptr) const;

    /**
     * @brief Modify this sprite to be drawn above the given one.
     */
    void put_above(const sprite_ptr& other);

    /**
     * @brief Modify this sprite to be drawn above the given regular background.
     */
    void put_above(const regular_bg_ptr& bg_ptr);

    /**
     * @brief Indicates if this sprite is flipped in the horizontal axis or not.
     */
    [[nodiscard]] bool horizontal_flip() const;

    /**
     * @brief Sets if this sprite is flipped in the horizontal axis or not.
     */
    void set_horizontal_flip(bool horizontal_flip);

    /**
     * @brief Indicates if this sprite is flipped in the vertical axis or not.
     */
    [[nodiscard]] bool vertical_flip() const;

    /**
     * @brief Sets if this sprite is flipped in the vertical axis or not.
     */
    void set_vertical_flip(bool vertical_flip);

    /**
     * @brief Indicates if the mosaic effect must be applied to this sprite or not.
     */
    [[nodiscard]] bool mosaic_enabled() const;

    /**
     * @brief Sets if the mosaic effect must be applied to this sprite or not.
     */
    void set_mosaic_enabled(bool mosaic_enabled);

    /**
     * @brief Indicates if blending must be applied to this sprite or not.
     */
    [[nodiscard]] bool blending_enabled() const;

    /**
     * @brief Sets if blending must be applied to this sprite or not.
     *
     * Keep in mind that blending and window attributes can't be enabled at the same time.
     */
    void set_blending_enabled(bool blending_enabled);

    /**
     * @brief Indicates if this sprite must be part of the silhouette of the sprite window or not.
     */
    [[nodiscard]] bool window_enabled() const;

    /**
     * @brief Sets if this sprite must be part of the silhouette of the sprite window or not.
     *
     * Keep in mind that blending and window attributes can't be enabled at the same time.
     */
    void set_window_enabled(bool window_enabled);

    /**
     * @brief Indicates if this sprite is being drawn
     * using more pixels than the area specified by its shape and size or not.
     */
    [[nodiscard]] bool double_size() const;

    /**
     * @brief Returns the way this sprite is drawn when its affine mat (if any)
     * requires more pixels than the area specified by the shape and size of the sprite.
     */
    [[nodiscard]] sprite_double_size_mode double_size_mode() const;

    /**
     * @brief Specifies the way this sprite is drawn when its affine mat (if any)
     * requires more pixels than the area specified by the shape and size of the sprite.
     */
    void set_double_size_mode(sprite_double_size_mode double_size_mode);

    /**
     * @brief Indicates if this sprite must be committed to the GBA or not.
     */
    [[nodiscard]] bool visible() const;

    /**
     * @brief Sets if this sprite must be committed to the GBA or not.
     */
    void set_visible(bool visible);

    /**
     * @brief Returns the camera attached to this sprite (if any).
     */
    [[nodiscard]] const optional<camera_ptr>& camera() const;

    /**
     * @brief Sets the camera attached to this sprite.
     * @param camera Camera to copy to this sprite.
     */
    void set_camera(const camera_ptr& camera);

    /**
     * @brief Sets the camera attached to this sprite.
     * @param camera Camera to move to this sprite.
     */
    void set_camera(camera_ptr&& camera);

    /**
     * @brief Remove the camera attached to this sprite (if any).
     */
    void remove_camera();

    /**
     * @brief Returns the affine mat attached to this sprite (if any).
     */
    [[nodiscard]] const optional<sprite_affine_mat_ptr>& affine_mat() const;

    /**
     * @brief Sets the affine mat attached to this sprite.
     *
     * This method calls set_remove_affine_mat_when_not_needed(false).
     *
     * @param affine_mat Affine mat to copy to this sprite.
     */
    void set_affine_mat(const sprite_affine_mat_ptr& affine_mat);

    /**
     * @brief Sets the affine mat attached to this sprite.
     *
     * This method calls set_remove_affine_mat_when_not_needed(false).
     *
     * @param affine_mat Affine mat to move to this sprite.
     */
    void set_affine_mat(sprite_affine_mat_ptr&& affine_mat);

    /**
     * @brief Remove the affine mat attached to this sprite (if any).
     */
    void remove_affine_mat();

    /**
     * @brief Indicates if the affine mat attached to this sprite (if any) must be removed
     * when it is not needed anymore.
     *
     * A sprite does not need an affine mat when its flipped_identity() method returns <b>true</b>.
     */
    [[nodiscard]] bool remove_affine_mat_when_not_needed() const;

    /**
     * @brief Sets if the affine mat attached to this sprite (if any) must be removed
     * when it is not needed anymore.
     *
     * A sprite does not need an affine mat when its flipped_identity() method returns <b>true</b>.
     */
    void set_remove_affine_mat_when_not_needed(bool remove_when_not_needed);

    /**
     * @brief Returns the attributes to commit to the first GBA register of this sprite.
     */
    [[nodiscard]] sprite_first_attributes first_attributes() const;

    /**
     * @brief Sets the attributes to commit to the first GBA register of this sprite.
     */
    void set_first_attributes(const sprite_first_attributes& first_attributes);

    /**
     * @brief Returns the attributes to commit to the second GBA register of this sprite when it is regular
     * (it does not have an attached affine mat).
     */
    [[nodiscard]] sprite_regular_second_attributes regular_second_attributes() const;

    /**
     * @brief Sets the attributes to commit to the second GBA register of this sprite when it is regular
     * (it does not have an attached affine mat).
     */
    void set_regular_second_attributes(const sprite_regular_second_attributes& second_attributes);

    /**
     * @brief Returns the attributes to commit to the second GBA register of this sprite when it is affine
     * (it hash an attached affine mat).
     */
    [[nodiscard]] sprite_affine_second_attributes affine_second_attributes() const;

    /**
     * @brief Sets the attributes to commit to the second GBA register of this sprite when it is affine
     * (it hash an attached affine mat).
     */
    void set_affine_second_attributes(const sprite_affine_second_attributes& second_attributes);

    /**
     * @brief Returns the attributes to commit to the third GBA register of this sprite.
     */
    [[nodiscard]] sprite_third_attributes third_attributes() const;

    /**
     * @brief Sets the attributes to commit to the third GBA register of this sprite.
     */
    void set_third_attributes(const sprite_third_attributes& third_attributes);

    /**
     * @brief Returns the internal handle.
     */
    [[nodiscard]] const void* handle() const
    {
        return _handle;
    }

    /**
     * @brief Exchanges the contents of this sprite_ptr with those of the other one.
     * @param other sprite_ptr to exchange the contents with.
     */
    void swap(sprite_ptr& other)
    {
        btn::swap(_handle, other._handle);
    }

    /**
     * @brief Exchanges the contents of a sprite_ptr with those of another one.
     * @param a First sprite_ptr to exchange the contents with.
     * @param b Second sprite_ptr to exchange the contents with.
     */
    friend void swap(sprite_ptr& a, sprite_ptr& b)
    {
        btn::swap(a._handle, b._handle);
    }

    /**
     * @brief Default equal operator.
     */
    [[nodiscard]] friend bool operator==(const sprite_ptr& a, const sprite_ptr& b) = default;

private:
    using handle_type = void*;

    handle_type _handle;

    explicit sprite_ptr(handle_type handle) :
        _handle(handle)
    {
    }

    void _destroy();
};


/**
 * @brief Hash support for sprite_ptr.
 *
 * @ingroup sprite
 */
template<>
struct hash<sprite_ptr>
{
    /**
     * @brief Returns the hash of the given sprite_ptr.
     */
    [[nodiscard]] unsigned operator()(const sprite_ptr& value) const
    {
        return make_hash(value.handle());
    }
};

}

#endif
