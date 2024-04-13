/*******************************************************************************
 *
 * @file      ExUtf32StringEncoding.cpp
 * @brief     Contains the ExUtf32StringEncoding exception class definition
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExUtf32StringEncoding.hpp>

namespace Junia {

ExUtf32StringEncoding::ExUtf32StringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location, const utf32_string& str, std::size_t index) noexcept
	: ExStringEncoding(msg, previous, location, index), str(str) { }

const utf32_string& ExUtf32StringEncoding::GetString() const noexcept {
	return this->str;
}

} // namespace Junia
