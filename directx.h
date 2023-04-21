#pragma once
#include "main.h"

typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice);

bool GetD3D9Device(void** pTable, size_t size);
HWND GetProcessWindow();

static HWND window;
extern int windowHeight;
extern int windowWidth;

extern LPDIRECT3DDEVICE9 pDevice;