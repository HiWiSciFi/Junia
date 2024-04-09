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

ExUnicodeStringEncoding::ExUnicodeStringEncoding(const std::u8string& msg, std::exception_ptr previous, CodePos location, const std::u32string& str, std::size_t index) noexcept
	: ExStringEncoding(msg, previous, location, index), str(str) { }

const std::u32string& ExUnicodeStringEncoding::GetString() const noexcept {
	return this->str;
}

} // namespace Junia
