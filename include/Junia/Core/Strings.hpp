/*******************************************************************************
 *
 * @file      Strings.hpp
 * @brief     Contains the specification for UTF8-String printing
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGS
#define __HEADER_JUNIA_CORE_STRINGS

#include "Core.hpp"

#include <ostream>
#include <string>

namespace std {

JUNIA_SYMBOL ostream& operator<<(ostream& os, const u8string& val);
JUNIA_SYMBOL ostream& operator<<(ostream& os, const char8_t* val);

} // namespace std

#endif // !defined(__HEADER_JUNIA_CORE_STRINGS)
