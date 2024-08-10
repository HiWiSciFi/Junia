/*******************************************************************************
 *
 * @file      Window.cpp
 * @brief     Contains the Window class implementation
 * @author    Max Hager
 * @date      2024-07-08
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include <Junia/Rendering/Window.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef GetMessage

#include <Junia/Core/StringConvert.hpp>
#include <Junia/Exceptions/ExWindows.hpp>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Rendering/Window.cpp";

namespace Junia {

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		default:
			return DefWindowProcW(hwnd, msg, wParam, lParam);
	}
}

struct Window::Impl {
	HWND hwnd = NULL;
};

Window::Window(const utf8_string& title, RenderAPI api) : impl(std::make_unique<Impl>()), api(api), title(title), shown(false) {
	this->impl = std::make_unique<Impl>();

	const wchar_t CLASS_NAME[] = L"JuniaWindowClass";

	HINSTANCE hInstance = GetModuleHandleW(NULL);

	WNDCLASSEXW wc = {
		.cbSize        = sizeof(WNDCLASSEXW),
		.lpfnWndProc   = WindowProc,
		.hInstance     = hInstance,
		.lpszClassName = CLASS_NAME
	};

	if (RegisterClassExW(&wc) == 0) {
		// throw
	}

	utf16_string u16Title = StringConvert::U8ToU16(this->title);

	this->impl->hwnd = CreateWindowExW(
		0,
		CLASS_NAME,
		u16Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	// TODO: if hwnd null throw
}

Window::~Window() {
}

void Window::HandleEvents() {
	MSG msg = {};
	while (PeekMessageW(&msg, this->impl->hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
}

void Window::Show() {
	ShowWindow(this->impl->hwnd, SW_SHOW);
	this->shown = true;
}

void Window::Hide() {
	ShowWindow(this->impl->hwnd, SW_HIDE);
	this->shown = false;
}

bool Window::IsShown() const {
	return this->shown;
}

bool Window::IsHidden() const {
	return !this->shown;
}

void Window::SetTitle(const utf8_string& title) {
	utf16_string wstr = StringConvert::U8ToU16(title);
	if (SetWindowTextW(this->impl->hwnd, wstr.c_str()) == 0) {
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
	}
	this->title = title;
}

utf8_string Window::GetTitle() const {
	return this->title;
}

Vec2i Window::GetPosition() const {
	RECT rect {};
	if (GetWindowRect(this->impl->hwnd, &rect) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
	return { static_cast<std::int32_t>(rect.left), static_cast<std::int32_t>(rect.top) };
}

void Window::SetPosition(Vec2i position) {
	if (SetWindowPos(this->impl->hwnd, NULL, position.x, position.y, 0, 0, SWP_NOACTIVATE | SWP_NOREPOSITION | SWP_NOSIZE | SWP_NOZORDER) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
}

Vec2ui Window::GetSize() const {
	RECT rect {};
	if (GetWindowRect(this->impl->hwnd, &rect) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
	return { static_cast<std::uint32_t>(rect.right - rect.left), static_cast<std::uint32_t>(rect.bottom - rect.top) };
}

void Window::SetSize(Vec2ui size) {
	if (SetWindowPos(this->impl->hwnd, NULL, 0, 0, size.x, size.y, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOREPOSITION | SWP_NOZORDER) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
}

bool Window::IsFocused() const {
	return GetFocus() == this->impl->hwnd;
}

void Window::RequestFocus() {
	if (SetFocus(this->impl->hwnd) == NULL) {
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
	}
}

void Window::RequestAttention() const {
	// TODO: consider using FlashWindowEx to allow continous flashing
	FlashWindow(this->impl->hwnd, TRUE);
}

Window::SizeMode Window::GetSizeMode() const {
	return SizeMode::REGULAR;
}

void Window::SetSizeMode(Window::SizeMode sizeMode) {
}

Window::FullscreenMode Window::GetFullscreenMode() const {
	return FullscreenMode::WINDOWED;
}

void Window::SetFullscreenMode(Window::FullscreenMode fullscreenMode) {
	if (fullscreenMode == FullscreenMode::FULLSCREEN) {
	}
}

} // namespace Junia
