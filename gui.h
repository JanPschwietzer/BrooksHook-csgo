#pragma once
#include "main.h"

namespace d3d9gui
{
	inline bool isOpen = true;
	inline bool isSetup = false;

	inline HWND window = nullptr;
	inline WNDCLASSEX windowClass = {};
	inline WNDPROC originalWindowProc = nullptr;

	bool SetupWindowClass(const char* windowClassName) noexcept;
	void DestroyWindowClass() noexcept;

	bool SetupWindow(const char* windowName) noexcept;
	void DestroyWindow() noexcept;

	void SetupDevice(LPDIRECT3DDEVICE9 pDevice);

	void SetupMenu(LPDIRECT3DDEVICE9 device) noexcept;
	void Destroy() noexcept;
	void Render() noexcept;
}