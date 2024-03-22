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

struct JUNIA_SYMBOL CodePos {
	const char* file;
	int         line;

	CodePos();
	CodePos(const char* file, int line);

	[[nodiscard]] bool IsProvided() const noexcept;

	[[nodiscard]] static CodePos NotProvided();
};

#define JUNIA_CODEPOS (::Junia::CodePos(__FILE__, __LINE__))

class JUNIA_SYMBOL Exception : public std::runtime_error {
public:
	explicit Exception(const char* msg, CodePos location) noexcept;

	[[nodiscard]] virtual const char* what() const final override;

	[[nodiscard]] bool        CodePosProvided() const noexcept;
	[[nodiscard]] const char* What() const noexcept;
	[[nodiscard]] const char* Where() const noexcept;

private:
	CodePos location;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_CORE_EXCEPTION)
