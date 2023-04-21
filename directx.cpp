#include "directx.h"

int windowHeight = 99;
int windowWidth = 99;

BOOL CALLBACK enumWindows(HWND handle, LPARAM lParam)
{
	DWORD procID;
	GetWindowThreadProcessId(handle, &procID);
	if (GetCurrentProcessId() != procID)
		return true;

	window = handle;
	return false;
}

HWND GetProcessWindow()
{
	window = nullptr;
	EnumWindows(enumWindows, NULL);

	int topbar = 35;
	int sidebar = 5;

	RECT size;
	GetWindowRect(window, &size);
	windowWidth = size.right - size.left - sidebar;
	windowHeight = size.bottom - size.top - topbar;

	return window;
}

bool GetD3D9Device(void** pTable, size_t size)
{
	if (!pTable)
		return false;

	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!pD3D)
		return false;

	IDirect3DDevice9* pDummy = nullptr;
	D3DPRESENT_PARAMETERS d3dpp = {};

	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetProcessWindow();

	HRESULT dummyCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummy);

	if (dummyCreated != S_OK)
	{
		d3dpp.Windowed = !d3dpp.Windowed;

		dummyCreated = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
			d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummy);

		if (dummyCreated != S_OK)
		{
			pD3D->Release();
			return false;
		}
	}

	memcpy(pTable, *(void***)(pDummy), size);
	pDummy->Release();
	return true;
}
