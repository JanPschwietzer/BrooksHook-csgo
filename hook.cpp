#include "hook.h"

void Patch(BYTE* dst, BYTE* src, int size)
{
	DWORD oldProtect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

bool Hook(char* src, char* dst, int len)
{
	if (len < 5)
		return false;

	//Replace original Function with JMP to own Address
	DWORD oldProtect;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(src, 0x90, len); //0x90 = NOP
	uintptr_t relAddy = (uintptr_t)(dst - src - 5);
	*src = (char)0xE9; //JMP
	*(uintptr_t*)(src + 1) = relAddy; //Address
	VirtualProtect(src, len, oldProtect, &oldProtect);
	return true;
}

char* TrampolineHook(char* src, char* dst, int len)
{
	if (len < 5)
		return nullptr;

	char* gateway = (char*)VirtualAlloc(0, len + 5, MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE);
	memcpy(gateway, src, len);
	uintptr_t jmpAddy = (uintptr_t)(src - gateway - 5);
	*(gateway + len) = (char)0xE9; //JMP
	*(uintptr_t*)(gateway + len + 1) = jmpAddy; //Address

	if (Hook(src, dst, len))
		return gateway;
	return nullptr;
}

