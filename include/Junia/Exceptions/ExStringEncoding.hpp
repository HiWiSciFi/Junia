/*******************************************************************************
 *
 * @file      ExStringEncoding.hpp
 * @brief     Contains the ExStringEncoding exception class definition
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_EXCEPTIONS_EXSTRINGENCODING
#define __HEADER_JUNIA_EXCEPTIONS_EXSTRINGENCODING

#include "../Core/Exception.hpp"

namespace Junia {

class JUNIA_SYMBOL ExStringEncoding : public Exception {
public:
	/**
	 * @brief ExStringEncoding object constructor
	 * @param msg      a text message explaining the exception
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	ExStringEncoding(const utf8_string& msg, std::exception_ptr previous = nullptr, CodePos location = CodePos::NotProvided()) noexcept;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_EXCEPTIONS_EXSTRINGENCODING)
