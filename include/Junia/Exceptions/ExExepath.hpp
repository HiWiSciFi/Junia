/*******************************************************************************
 *
 * @file      ExExepath.hpp
 * @brief     Contains the ExExepath class definition
 * @author    Max Hager
 * @date      2024-07-10
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_EXCEPTIONS_EXEXEPATH
#define __HEADER_JUNIA_EXCEPTIONS_EXEXEPATH

#include "../Core/Core.hpp"
#include "../Core/Exception.hpp"

namespace Junia {

class JUNIA_SYMBOL ExExepath : public Exception {
	/**
	 * @brief ExExepath object constructor
	 * @param msg      a text message explaining the exception
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	ExExepath(const utf8_string& msg, std::exception_ptr previous, CodePos location);
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_EXCEPTIONS_EXEXEPATH)
