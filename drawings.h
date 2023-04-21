#pragma once
#include "main.h"

#define ABS(x) ((x < 0) ? (-x) : (x))

void DrawFilledRect(int x, int y, int width, int height, D3DCOLOR color);
void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color);

void DrawEspBox2D(float topX, float topY, float bottomX, float bottomY, int thickness, D3DCOLOR color);
void DrawHealth(float topX, float topY, float bottomY, int thickness, int& health);
void DrawArmor(float topX, float topY, float bottomY, int thickness, int& armor);
void DrawCrosshair();
void DrawSnaplines(float positionX, float positionY, D3DCOLOR color);