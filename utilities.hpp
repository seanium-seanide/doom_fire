#pragma once

namespace utilities
{
/**
 * @brief Map a value from one range to another
 *
 * @param val The value to be mapped
 * @param x1  The start of the source range
 * @param x2  The end of the source range
 * @param y1  The start of the destination range
 * @param y2  The end of the destination range
 */
template <typename T>
T lerp(T x, T x1, T x2, T y1, T y2);

/**
 * @brief Return the upper limit if the value is greater.
 *   Return the lower limit if the value is lower.
 */
template <typename T>
T clamp(T x, T min, T max);
}


#include <utilities.tpp>
