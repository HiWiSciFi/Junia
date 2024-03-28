/*******************************************************************************
 *
 * @file      StringConvert.cpp
 * @brief     Contains the class implementation for the string conversion class
 * @author    Max Hager
 * @date      22.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/StringConvert.hpp>

#include <bit>
#include <stdexcept>
#include <vector>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Core/StringConvert.cpp";

namespace Junia {

u_string StringConvert::UTF8ToUnicode(const utf8_string& utf8) {
	u_string unicode;

	for (std::size_t i = 0; i < utf8.size(); i++) {
		unsigned char c = std::bit_cast<const unsigned char>(utf8[i]);

		if (c >= 0x00 && c <= 0x7F) {
			unicode += c & 0x7F;
		} else if (c >= 0xC0 && c <= 0xDF) {
			if (i + 1 >= utf8.size()) throw ExUtf8StringEncoding("Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			u_string::value_type point = c & 0x1F;
			c                          = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else if (c >= 0xE0 && c <= 0xEF) {
			if (i + 2 >= utf8.size()) throw ExUtf8StringEncoding("Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			u_string::value_type point = c & 0x0F;
			c                          = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else if (c >= 0xF0 && c <= 0xF7) {
			if (i + 3 >= utf8.size()) throw ExUtf8StringEncoding("Invalid UTF-8 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
			u_string::value_type point = c & 0x07;
			c                          = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			c     = utf8[++i];
			if (c < 0x80 || c > 0xBF) throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i - 1);
			point = (point << 6) | (c & 0x3F);
			unicode += point;
		} else {
			throw ExUtf8StringEncoding("Invalid UTF-8 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf8, i);
		}
	}

	return unicode;
}

utf8_string StringConvert::UnicodeToUTF8(const u_string& unicode) {
	utf8_string utf8;

	for (std::size_t i = 0; i < unicode.size(); i++) {
		u_string::value_type point = unicode[i];

		if (point >= 0 && point <= 0x007F) {
			utf8 += static_cast<utf8_string::value_type>(point & 0xFF);
		} else if (point >= 0x80 && point <= 0x07FF) {
			utf8 += static_cast<utf8_string::value_type>(0xC0 | (point >> 6));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else if (point >= 0x800 && point <= 0xFFFF) {
			utf8 += static_cast<utf8_string::value_type>(0xE0 | (point >> 12));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 6) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else if (point >= 0x10000 && point <= 0x10FFFF) {
			utf8 += static_cast<utf8_string::value_type>(0xF0 | (point >> 18));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 12) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | ((point >> 6) & 0x3F));
			utf8 += static_cast<utf8_string::value_type>(0x80 | (point & 0x3F));
		} else
			throw ExUnicodeStringEncoding("Invalid Unicode codepoint encountered", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), unicode, i);
	}

	return utf8;
}

u_string StringConvert::UTF16ToUnicode(const utf16_string& utf16) {
	u_string unicode;

	for (std::size_t i = 0; i < utf16.size(); i++) {
		utf16_string::value_type c = utf16[i];

		if (c >= 0xD800 && c <= 0xDBFF) {
			if (utf16.size() <= i + 1) throw ExUtf16StringEncoding("Invalid UTF-16 string. Not enough characters.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf16, i);
			u_string::value_type point = (c - 0xD800) << 10;

			c = utf16[++i];
			if (c < 0xDC00 || c > 0xDFFF) throw ExUtf16StringEncoding("Invalid UTF-16 string. Unexpected character encountered.", nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__), utf16, i - 1);
			point += c - 0xDC00;

			point += 0x10000;
			unicode += point;
		} else {
			unicode += c;
		}
	}

	return unicode;
}

utf16_string StringConvert::UnicodeToUTF16(const u_string& unicode) {
	utf16_string utf16;

	for (std::size_t i = 0; i < unicode.size(); i++) {
		u_string::value_type point = unicode[i];

		if (point < 0xD800 || (point > 0xDFFF && point < 0x10000)) {
			utf16 += static_cast<utf16_string::value_type>(point & 0xFFFF);
		} else {
			point -= 0x10000;
			utf16 += (point >> 10) + 0xD800;
			utf16 += (point & 0x3FF) + 0xDC00;
		}
	}

	return utf16;
}

utf16_string StringConvert::UTF8ToUTF16(const utf8_string& utf8) {
	// may throw ExUtf8StringEncoding or ExUnicodeStringEncoding
	return UnicodeToUTF16(UTF8ToUnicode(utf8));
}

utf8_string StringConvert::UTF16ToUTF8(const utf16_string& utf16) {
	// may throw ExUtf16StringEncoding or ExUnicodeStringEncoding
	return UnicodeToUTF8(UTF16ToUnicode(utf16));
}

} // namespace Junia
