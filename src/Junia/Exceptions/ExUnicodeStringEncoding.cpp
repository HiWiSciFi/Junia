/*******************************************************************************
 *
 * @file      ExUnicodeStringEncoding.cpp
 * @brief     Contains the ExUnicodeStringEncoding exception class definition
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExUnicodeStringEncoding.hpp>

namespace Junia {

ExUnicodeStringEncoding::ExUnicodeStringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location, const u_string& str, std::size_t index) noexcept
	: ExStringEncoding(msg, previous, location, index), str(str) { }

const u_string& ExUnicodeStringEncoding::GetString() const noexcept {
	return this->str;
}

} // namespace Junia
