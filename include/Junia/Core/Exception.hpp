/*******************************************************************************
 *
 * @file      Exception.hpp
 * @brief     Contains the definition of the Base exception class
 * @author    Max Hager
 * @date      18.03.2024
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_CORE_EXCEPTION
#define __HEADER_JUNIA_CORE_EXCEPTION

#include "Core.hpp"

#include <stdexcept>
#include <string>

namespace Junia {

struct CodePos {
	const char* file;
	int         line;

	CodePos();
	CodePos(const char* file, int line);

	[[nodiscard]] bool IsProvided() const;

	[[nodiscard]] static CodePos NotProvided();
};

#define JUNIA_CODEPOS (::Junia::CodePos(__FILE__, __LINE__))

class JUNIA_SYMBOL Exception : public std::runtime_error {
public:
	Exception(const char* msg, CodePos location);

private:
	CodePos location;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_EXCEPTION)
