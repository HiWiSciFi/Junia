/*******************************************************************************
 *
 * @file      Rect.hpp
 * @brief     Contains the Rect class definition
 * @author    Max Hager
 * @date      2024-07-21
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_MATH_RECT
#define __HEADER_JUNIA_MATH_RECT

#include "Types.hpp"

namespace Junia {

template <typename T>
struct Rect {
public:
	T l, r, t, b;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_MATH_RECT)
