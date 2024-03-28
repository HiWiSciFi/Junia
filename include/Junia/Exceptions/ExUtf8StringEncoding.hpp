/*******************************************************************************
 *
 * @file      ExUtf8StringEncoding.hpp
 * @brief     Contains the ExUtf8StringEncoding exception class definition
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_EXCEPTIONS_EXUTF8STRINGENCODING
#define __HEADER_JUNIA_EXCEPTIONS_EXUTF8STRINGENCODING

#include "ExStringEncoding.hpp"

namespace Junia {

class JUNIA_SYMBOL ExUtf8StringEncoding : public ExStringEncoding {
public:
	/**
	 * @brief ExUtf8StringEncoding object constructor
	 * @param msg      a text message explaining the exception
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 * @param str      the string that caused the exception
	 * @param index    the index of the character that caused the exception
	 */
	ExUtf8StringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location, const utf8_string& str, std::size_t index) noexcept;

	/**
	 * @brief   get the string that caused the exception
	 * @returns the string that caused the exception
	 */
	const utf8_string& GetString() const noexcept;

protected:
	utf8_string str;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_EXCEPTIONS_EXUTF8STRINGENCODING)
