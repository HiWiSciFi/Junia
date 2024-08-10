/*******************************************************************************
 *
 * @file      Types.hpp
 * @brief     Contains the Math types template definitions
 * @author    Max Hager
 * @date      2024-07-21
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_MATH_TYPES
#define __HEADER_JUNIA_MATH_TYPES

#include <cstdint>

namespace Junia {

template <std::uint8_t S, typename T>
struct Vector;

template <std::uint8_t C, std::uint8_t R, typename T>
struct Matrix;

template <typename T>
struct Quat;

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_MATH_TYPES)
