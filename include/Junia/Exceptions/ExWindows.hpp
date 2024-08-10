/*******************************************************************************
 *
 * @file      ExWindows.hpp
 * @brief     Contains the ExWindows class definition
 * @author    Max Hager
 * @date      2024-07-10
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_EXCEPTIONS_EXWINDOWS
#define __HEADER_JUNIA_EXCEPTIONS_EXWINDOWS

#include "../Core/Core.hpp"
#include "../Core/Exception.hpp"

#include <exception>

namespace Junia {

class JUNIA_SYMBOL ExWindows : public Exception {
public:
	/**
	 * @brief ExWindows object constructor. Will set the message to
	 *        "Win32 Error Code <code>" if the message text could not be
	 *        retrieved from the system.
	 * @param code     the exception code of the message
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	ExWindows(unsigned long code, std::exception_ptr previous, CodePos location) noexcept;

protected:
	unsigned long code;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_EXCEPTIONS_EXWINDOWS)
