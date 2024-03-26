/*******************************************************************************
 *
 * @file      Strings.hpp
 * @brief     Contains the class definition for Junia String classes
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGS
#define __HEADER_JUNIA_CORE_STRINGS

#include <sstream>
#include <string>

namespace Junia {

using ucodepoint_t       = char32_t;                                                                                            // a unicode codepoint
using utf8_string        = std::string;                                                                                         // a string of UTF-8 encoded characters
using utf8_stringstream  = std::stringstream;                                                                                   // a string stream for UTF-8 encoded strings
using u_string           = std::basic_string<ucodepoint_t, std::char_traits<ucodepoint_t>, std::allocator<ucodepoint_t>>;       // a string of unicode codepoints
using u_stringstream     = std::basic_stringstream<ucodepoint_t, std::char_traits<ucodepoint_t>, std::allocator<ucodepoint_t>>; // a string stream of unicode codepoints
using utf16_string       = std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;                      // a string of UTF-16 encoded characters
using utf16_stringstream = std::basic_stringstream<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>;                // a string stream for UTF-16 encoded strings

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_STRINGS)
