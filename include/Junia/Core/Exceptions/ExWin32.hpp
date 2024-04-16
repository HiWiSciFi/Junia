/*******************************************************************************
 *
 * @file      ExWin32.hpp
 * @brief     Contains the ExWin32 exception class definition
 * @author    Max Hager
 * @date      13.04.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_EXCEPTIONS_EXWIN32
#define __HEADER_JUNIA_CORE_EXCEPTIONS_EXWIN32

#include "../Exception.hpp"

namespace Junia {

class JUNIA_SYMBOL ExWin32 : public Exception {
public:
	/**
	 * @brief ExWin32 object constructor. Will set the message to
	 *        "Win32 Error Code <code>" if the message text could not be
	 *        retrieved from the system.
	 * @param code     the exception code of the message
	 * @param previous an exception that led to this exception or a nullptr
	 * @param location the code position this exception was thrown in (see
	 *                 JUNIA_CODEPOS)
	 */
	ExWin32(unsigned long code, std::exception_ptr previous, CodePos location) noexcept;

protected:
	unsigned long code;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_EXCEPTIONS_EXWIN32)
