/*******************************************************************************
 *
 * @file      JGL_Instance.cpp
 * @brief     Contains the JGL_Instance class implementation
 * @author    Max Hager
 * @date      2024-07-11
 * @copyright © Max Hager, 2024. All right reserved.
 *
 ******************************************************************************/

#include "JGL_Instance.hpp"

#include <Junia/Exceptions/ExWindows.hpp>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef _WIN32_LEAN_AND_MEAN
#include <glad/wgl.h>
#include <iostream>

static constexpr const char* CURRENT_FILE_NAME = "Junia/src/Junia/Rendering/OpenGL/JGL_Instance.cpp";

namespace Junia::JGL {

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

static const wchar_t     DUMMY_WINDOW_CLASS_NAME[] = L"JuniaGLDummyWindowClass";
static const WNDCLASSEXW DUMMY_WINDOW_CLASS        = {
		   .cbSize        = sizeof(DUMMY_WINDOW_CLASS),
		   .lpfnWndProc   = DefWindowProcW,
		   .hInstance     = GetModuleHandleW(NULL),
		   .lpszClassName = DUMMY_WINDOW_CLASS_NAME
};

static HWND CreateDummyWindow() {
	HINSTANCE hInstance = GetModuleHandleW(NULL);

	if (RegisterClassExW(&DUMMY_WINDOW_CLASS) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

	HWND window = CreateWindowExW(
		0,
		DUMMY_WINDOW_CLASS_NAME,
		L"DUMMYWINDOW",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		DUMMY_WINDOW_CLASS.hInstance,
		NULL);

	if (window == NULL)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));

	return window;
}

static void DestroyDummyWindow() {
	if (UnregisterClassW(DUMMY_WINDOW_CLASS.lpszClassName, DUMMY_WINDOW_CLASS.hInstance) == 0)
		throw ExWindows(GetLastError(), nullptr, CodePos(CURRENT_FILE_NAME, __FUNCTION__, __LINE__));
}

JGL_Instance::JGL_Instance() {
	HWND dummyWindow = CreateDummyWindow();

	HDC device = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pfd = {
		.nSize        = sizeof(pfd),
		.nVersion     = 1,
		.dwFlags      = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		.iPixelType   = PFD_TYPE_RGBA,
		.cColorBits   = 32,
		.cDepthBits   = 24,
		.cStencilBits = 8,
		.iLayerType   = PFD_MAIN_PLANE
	};
	int pixelFormat = ChoosePixelFormat(device, &pfd);
	SetPixelFormat(device, pixelFormat, &pfd);

	HGLRC tempContext = wglCreateContext(device);

	wglMakeCurrent(device, tempContext);

	if (!gladLoaderLoadGL()) {
		std::cerr << "ERROR: Failed to initialize GL" << std::endl;
	}

	if (!gladLoadWGL(device, (GLADloadfunc)wglGetProcAddress)) {
		std::cerr << "ERROR: Failed to initialize WGL" << std::endl;
	}

	/*int attribs[] = {
		WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
		WGL_CONTEXT_MINOR_VERSION_ARB, 6,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
		0
	};

	HGLRC context = wglCreateContextAttribsARB(device, 0, attribs);*/

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempContext);
	/*wglMakeCurrent(device, context);

	ShowWindow(dummyWindow, SW_SHOW);

	auto error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << error << std::endl;
	}

	RECT rect;
	GetWindowRect(dummyWindow, &rect);
	glViewport(0, 0, rect.right - rect.left, rect.bottom - rect.top);
	glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

	MSG msg = {};
	while (msg.message != WM_QUIT) {
		while (PeekMessageW(&msg, dummyWindow, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		glClear(GL_COLOR_BUFFER_BIT);
		SwapBuffers(device);
	}

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(context);*/
	ReleaseDC(dummyWindow, device);
	DestroyWindow(dummyWindow);
}

} // namespace Junia::JGL
