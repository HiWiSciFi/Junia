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

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string& val) {
	if constexpr (sizeof(char) == sizeof(Junia::utf8_string::value_type)) {
		os.write(reinterpret_cast<const char*>(val.data()), val.size());
	} else {
		for (std::size_t i = 0; i < val.size(); i++) {
			os.put(static_cast<char>(val[i]));
		}
	}
	return os;
}

JUNIA_SYMBOL ostream& operator<<(ostream& os, const Junia::utf8_string::value_type* val) {
	os.write(reinterpret_cast<const char*>(val), strlen(reinterpret_cast<const char*>(val)));
	return os;
}

} // namespace std
