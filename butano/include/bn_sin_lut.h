/*
 * Copyright (c) 2020-2021 Gustavo Valiente gustavo.valiente@protonmail.com
 * zlib License, see LICENSE file.
 */

/*
 * Copyright (c) 2011-2015, 2019-2020 Antonio Niño Díaz <antonio_nd@outlook.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef BN_SIN_LUT_H
#define BN_SIN_LUT_H

/**
 * @file
 * bn::sin_lut header file.
 *
 * @ingroup math
 */

#include "bn_array.h"

namespace bn
{

/**
 * @brief Calculates the value to store in sin_lut for the given angle.
 * @param lut_angle sin_lut angle (360 degrees = 65536).
 * @return Sine value in the range [-4096, 4096].
 *
 * @ingroup math
 */
[[nodiscard]] constexpr int calculate_sin_lut_value(int lut_angle)
{
    // https://github.com/AntonioND/ugba/blob/master/libugba/source/fp_math.c

    constexpr const int FP_PI = 0x8000;
    constexpr const int FP_PI_2 = FP_PI / 2;
    constexpr const int FP_2_PI = 2 * FP_PI;

    // First, use symmetry to clamp to -pi/2 to +pi/2 (-0x4000 to 0x4000)

    int x = lut_angle;
    x &= FP_2_PI - 1;

    if (x >= (3 * FP_PI_2)) // 3*pi/2 to 2*pi
        x = x - FP_2_PI;
    else if (x > FP_PI_2) // pi/2 to 3*pi/2
        x = FP_PI - x;

    // Calculate result

    constexpr const double pi = 3.1415926535897932384626433832795;
    constexpr const auto A = int32_t(((2.0 * pi) * (1 << 24))); // 8.24
    constexpr const auto B = int32_t((1 << 7) * (12.0 / pi - 1.0 - pi) * (1 << 24)); // 8.24
    constexpr const auto C = int32_t((1 << 9) * 3.0 * (2.0 + pi - 16.0 / pi) * (1 << 24)); // 8.24

    int64_t X2 = x * x; // 16.0 * 16.0 = 32.0

    int32_t T1 = (X2 * C) >> 32; // (32.0 * 8.24) >> 32 = 40.24 >> 32 = 8.24

    // ((32.0 + 32.0) * 8.24) >> 32 = (32.0 * 8.24) >> 32 = 40.24 >> 32 = 8.24
    int32_t T2 = ((B + T1) * X2) >> 32;

    // Prepare X so that the final shift is by 32
    x = x << 8; // 16.8

    int64_t result = A + T2; // 8.24
    result *= x; // 24.32

    // Add 0.5 to round up before the final shift
    result += (1U << 31); // 24.32
    result >>= 32; // 24.0

    return int(result >> 4);
}

/**
 * @brief A sine LUT of 16bit values in 4.12 format.
 *
 * @ingroup math
 */
constexpr const array<int16_t, 2049> sin_lut = []{
    array<int16_t, 2049> result;
    int lut_angle = 0;

    for(int index = 0; index < 2049; ++index)
    {
        result[index] = int16_t(calculate_sin_lut_value(lut_angle));
        lut_angle += 65536 / 2048;
    }

    return result;
}();

}

#endif
