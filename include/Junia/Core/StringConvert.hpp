/*******************************************************************************
 *
 * @file      StringConvert.hpp
 * @brief     Contains the class definition for the string conversion class
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/
#ifndef __HEADER_JUNIA_CORE_STRINGCONVERT
#define __HEADER_JUNIA_CORE_STRINGCONVERT

#include "Core.hpp"

#include "Strings.hpp"

namespace Junia {

class JUNIA_SYMBOL StringConvert final {
public:
	static u_string     UTF8ToUnicode(const utf8_string& utf8);
	static utf8_string  UnicodeToUTF8(const u_string& unicode);
	static u_string     UTF16ToUnicode(const utf16_string& utf16);
	static utf16_string UnicodeToUTF16(const u_string& unicode);
	static utf16_string UTF8ToUTF16(const utf8_string& utf8);
	static utf8_string  UTF16ToUTF8(const utf16_string& utf16);

private:
	StringConvert()                     = delete;
	StringConvert(const StringConvert&) = delete;
	~StringConvert()                    = delete;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_STRINGCONVERT)
