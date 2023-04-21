#include "drawings.h"

extern Hack* hack;

void DrawFilledRect(int x, int y, int width, int height, D3DCOLOR color)
{
	D3DRECT rect = { x, y, x + width, y + height };

	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawLine(int x1, int y1, int x2, int y2, int thickness, D3DCOLOR color)
{
	if (!hack->lineL)
		D3DXCreateLine(pDevice, &hack->lineL);

	D3DXVECTOR2 line[2];
	line[0] = D3DXVECTOR2(x1, y1);
	line[1] = D3DXVECTOR2(x2, y2);
	hack->lineL->SetWidth(thickness);
	hack->lineL->Draw(line, 2, color);
}

void DrawEspBox2D(float topX, float topY, float bottomX, float bottomY, int thickness, D3DCOLOR color)
{
	int height = ABS(topY - bottomY);
	Vec2 topLeft, topRight, bottomLeft, bottomRight;

	topLeft.x = topX - height / 4;
	topRight.x = topX + height / 4;
	topLeft.y = topY;
	topRight.y = topY;
	bottomLeft.y = bottomY;
	bottomRight.y = bottomY;

	DrawLine(topLeft.x, topLeft.y, topRight.x, topRight.y, thickness, color);
	DrawLine(topLeft.x, bottomLeft.y, topRight.x, bottomRight.y, thickness, color);

	DrawLine(topLeft.x, topLeft.y, topLeft.x, bottomLeft.y, thickness, color);
	DrawLine(topRight.x, topRight.y, topRight.x, bottomRight.y, thickness, color);
}

void DrawHealth(float topX, float topY, float bottomY, int thickness, int& health)
{
	int height = ABS(topY - bottomY);
	int xStart = topX + height / 4;
	int healthBar = topY - (topY - bottomY) / 100 * health;

	DrawLine(xStart + 5, topY, xStart + 5, bottomY, 3, D3DCOLOR_ARGB(255, 0, 0, 0));
	if (health > 60)
	{
		DrawLine(xStart + 5, healthBar, xStart + 5, topY, 3, D3DCOLOR_ARGB(255, 124, 252, 0));
	}
	else if (health > 20)
	{
		DrawLine(xStart + 5, healthBar, xStart + 5, topY, 3, D3DCOLOR_ARGB(255, 255, 252, 0));
	}
	else
	{
		DrawLine(xStart + 5, healthBar, xStart + 5, topY, 3, D3DCOLOR_ARGB(255, 255, 0, 0));
	}

}

void DrawArmor(float topX, float topY, float bottomY, int thickness, int& armor)
{
	int height = ABS(topY - bottomY);
	int xStart = topX + height / 4;
	int armorBar = topY - (topY - bottomY) / 100 * armor;

	DrawLine(xStart + 9, topY, xStart + 9, bottomY, 3, D3DCOLOR_ARGB(255, 0, 0, 0));
	DrawLine(xStart + 9, armorBar, xStart + 9, topY, 3, D3DCOLOR_ARGB(255, 127, 206, 241));

}

void DrawCrosshair()
{
	DrawLine(hack->crosshair2D.x - 4,
		hack->crosshair2D.y,
		hack->crosshair2D.x + 5,
		hack->crosshair2D.y,
		1, D3DCOLOR_ARGB(255, 255, 0, 0));
	DrawLine(hack->crosshair2D.x,
		hack->crosshair2D.y - 4,
		hack->crosshair2D.x,
		hack->crosshair2D.y + 5,
		1, D3DCOLOR_ARGB(255, 255, 0, 0));
}

void DrawSnaplines(float positionX, float positionY, D3DCOLOR color)
{
	DrawLine(positionX, positionY, windowWidth / 2, windowHeight, 1, color);
}
