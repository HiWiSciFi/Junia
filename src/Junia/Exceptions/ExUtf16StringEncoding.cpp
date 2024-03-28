/*******************************************************************************
 *
 * @file      ExUtf16StringEncoding.cpp
 * @brief     Contains the ExUtf16StringEncoding exception class implementation
 * @author    Max Hager
 * @date      27.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Exceptions/ExUtf16StringEncoding.hpp>

namespace Junia {

ExUtf16StringEncoding::ExUtf16StringEncoding(const utf8_string& msg, std::exception_ptr previous, CodePos location, const utf16_string& str, std::size_t index) noexcept
	: ExStringEncoding(msg, previous, location, index), str(str) { }

} // namespace Junia
