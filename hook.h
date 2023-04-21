#pragma once
#include "main.h"


void Patch(BYTE* dst, BYTE* src, int size);

bool Hook(char* src, char* dst, int len);

char* TrampolineHook(char* src, char* dst, int len);