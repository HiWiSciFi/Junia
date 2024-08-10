/*******************************************************************************
 *
 * @file      Window.hpp
 * @brief     Contains the Window class definition
 * @author    Max Hager
 * @date      2024-07-08
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#ifndef __HEADER_JUNIA_RENDERING_WINDOW
#define __HEADER_JUNIA_RENDERING_WINDOW

#include "../Core/Core.hpp"
#include "../Core/Strings.hpp"
#include "../Math/Vector2.hpp"
#include "Monitor.hpp"
#include "RenderAPI.hpp"

#include <memory>

namespace Junia {

class JUNIA_SYMBOL Window {
public:
	/**
	 * @brief The size states a window can enter
	 */
	enum class SizeMode : std::uint8_t {
		REGULAR   = 0,
		ICONIFIED = 1,
		MAXIMIZED = 2
	};

	/**
	 * @brief The Fullscreen states a window can enter
	 */
	enum class FullscreenMode : std::uint8_t {
		WINDOWED              = 0,
		BORDERLESS_FULLSCREEN = 1,
		FULLSCREEN            = 2
	};

	Window(const utf8_string& title, RenderAPI api);
	~Window();

	void HandleEvents();

	void Show();

	void Hide();

	[[nodiscard]] bool IsShown() const;

	[[nodiscard]] bool IsHidden() const;

	void SetTitle(const utf8_string& title);

	[[nodiscard]] utf8_string GetTitle() const;

	[[nodiscard]] Vec2i GetPosition() const;
	void                SetPosition(Vec2i position);

	[[nodiscard]] Vec2ui GetSize() const;
	void                 SetSize(Vec2ui size);

	[[nodiscard]] bool IsFocused() const;

	void RequestFocus();

	void RequestAttention() const;

	[[nodiscard]] Window::SizeMode GetSizeMode() const;

	void SetSizeMode(Window::SizeMode sizeMode);

	[[nodiscard]] Window::FullscreenMode GetFullscreenMode() const;

	void SetFullscreenMode(Window::FullscreenMode fullscreenMode);

private:
	struct Impl;
	std::unique_ptr<Impl> impl;

	RenderAPI   api;
	utf8_string title;
	bool        shown;
};

} // namespace Junia

#endif // !defined(__HEADER_JUNIA_RENDERING_WINDOW)
