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

/**
 *
 * @class StringConvert
 * @brief Static class to convert strings between encodings
 *
 */
class JUNIA_SYMBOL StringConvert final {
public:
	/**
	 * @brief        Decode a UTF-8 string to a string of unicode codepoints
	 * @param   utf8 The UTF-8 string to decode
	 * @returns      A string of unicode codepoints
	 */
	static u_string UTF8ToUnicode(const utf8_string& utf8);

	/**
	 * @brief           Encode a string of unicode codepoints in UTF-8
	 * @param   unicode The string of unicode codepoints to encode
	 * @returns         A UTF-8 encoded string
	 */
	static utf8_string UnicodeToUTF8(const u_string& unicode);

	/**
	 * @brief         Decode a UTF-16 string to a string of unicode codepoints
	 * @param   utf16 The UTF-16 string to decode
	 * @returns       A string of unicode codepoints
	 */
	static u_string UTF16ToUnicode(const utf16_string& utf16);

	/**
	 * @brief           Encode a string of unicode codepoints in UTF-16
	 * @param   unicode The string of unicode codepoints to encode
	 * @returns         A UTF-16 encoded string
	 */
	static utf16_string UnicodeToUTF16(const u_string& unicode);

	/**
	 * @brief        Convert a UTF-8 encoded string to a UTF-16 encoded string
	 * @param   utf8 The UTF-8 string to convert
	 * @returns      A UTF-16 encoded string
	 */
	static utf16_string UTF8ToUTF16(const utf8_string& utf8);

	/**
	 * @brief         Convert a UTF-16 encoded string to a UTF-8 encoded string
	 * @param   utf16 The UTF-16 string to convert
	 * @returns       A UTF-8 encoded string
	 */
	static utf8_string UTF16ToUTF8(const utf16_string& utf16);

private:
	StringConvert()                     = delete;
	StringConvert(const StringConvert&) = delete;
	~StringConvert()                    = delete;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_STRINGCONVERT)
