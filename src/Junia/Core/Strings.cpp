/*******************************************************************************
 *
 * @file      Strings.cpp
 * @brief     Contains the specification for UTF8-String printing
 * @author    Max Hager
 * @date      9.04.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Core/Strings.hpp>

namespace std {

JUNIA_SYMBOL ostream& operator<<(ostream& os, const u8string& val) {
	os.write(reinterpret_cast<const char*>(val.data()), val.size());
	return os;
}

JUNIA_SYMBOL ostream& operator<<(ostream& os, const char8_t* val) {
	os.write(reinterpret_cast<const char*>(val), strlen(reinterpret_cast<const char*>(val)));
	return os;
}

} // namespace std
