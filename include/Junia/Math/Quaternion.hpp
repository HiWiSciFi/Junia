/*******************************************************************************
 *
 * @file      Quaternion.hpp
 * @brief     Contains the Quaternion class definition
 * @author    Max Hager
 * @date      2024-07-21
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_MATH_QUATERNION
#define __HEADER_JUNIA_MATH_QUATERNION

#include "Types.hpp"

namespace Junia {

using Quaternion   = Quat<float>;
using fQuaternion  = Quat<float>;
using dQuaternion  = Quat<double>;
using iQuaternion  = Quat<std::int32_t>;
using uiQuaternion = Quat<std::uint32_t>;

#ifdef _MSC_VER
#pragma pack(push, 1)
#endif

template <typename T>
struct Quat {
private:
	static constexpr unsigned char length() { return 4; }

public:
	T x, y, z, w;
}
#if defined(__GNUC__) || defined(__clang__)
__attribute__((__packed__))
#endif
;

#ifdef _MSC_VER
#pragma pack(pop)
#endif

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_MATH_QUATERNION)
