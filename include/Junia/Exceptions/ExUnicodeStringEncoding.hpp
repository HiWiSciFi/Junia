/*******************************************************************************
 *
 * @file      ExUnicodeStringEncoding.hpp
 * @brief     Contains the ExUnicodeStringEncoding exception class
 *            implementation
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_EXCEPTIONS_EXUNICODESTRINGENCODING
#define __HEADER_JUNIA_EXCEPTIONS_EXUNICODESTRINGENCODING

#include "ExStringEncoding.hpp"

namespace Junia {

class JUNIA_SYMBOL ExUnicodeStringEncoding : public ExStringEncoding {
public:
	/**
	 * @brief ExUnicodeStringEncoding object constructor
	 * @param msg      a text message explaining the exception
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 * @param str      the string that caused the exception
	 * @param index    the index of the character that caused the exception
	 */
	ExUnicodeStringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location, const u_string& str, std::size_t index) noexcept;

protected:
	u_string str;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_EXCEPTIONS_EXUNICODESTRINGENCODING)
