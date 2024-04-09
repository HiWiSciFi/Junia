/*******************************************************************************
 *
 * @file      ExUtf8StringEncoding.cpp
 * @brief     Contains the ExUtf8StringEncoding exception class implementation
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExUtf8StringEncoding.hpp>

namespace Junia {

ExUtf8StringEncoding::ExUtf8StringEncoding(const std::u8string& msg, std::exception_ptr previous, CodePos location, const std::u8string& str, std::size_t index) noexcept
	: ExStringEncoding(msg, previous, location, index), str(str) { }

const std::u8string& ExUtf8StringEncoding::GetString() const noexcept {
	return this->str;
}

} // namespace Junia
