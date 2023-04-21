#include "main.h"

void* d3d9Device[119];
BYTE EndSceneBytes[7]{ 0 };
tEndScene originalEndScene = nullptr;
extern LPDIRECT3DDEVICE9 pDevice = nullptr;
Hack* hack;

void APIENTRY hkEndScene(LPDIRECT3DDEVICE9 original_pDevice)
{
	if (!pDevice)
	{
		pDevice = original_pDevice;
		d3d9gui::SetupDevice(pDevice);
		d3d9gui::SetupMenu(pDevice);
	}
	if (d3d9gui::isOpen)
	{
		d3d9gui::Render();
	}
	else if (hack->entityList->entities[0].entity)
	{
		for (int i = 1; i < 32; i++)
		{
			Entity* localPlayer = hack->entityList->entities[0].entity;
			Entity* currentEntity = hack->entityList->entities[i].entity;
			if (!hack->CheckValidEntity(currentEntity))
				continue;

			Vec2 entityPosition2D, entityHead2D;

			if (enableVisuals)
			{
				if (hack->WorldToScreen(currentEntity->vecOrigin, entityPosition2D))
				{
					Vec3 entityHead3D = hack->GetBonePosition(currentEntity, 8);
					entityHead3D.z += 8;

					if (currentEntity->iTeamNumber == localPlayer->iTeamNumber)
					{
						//OWN TEAM FUNCTIONS
						if (espF)
						{
							if (hack->WorldToScreen(entityHead3D, entityHead2D))
							{
								if (hack->IsVisible(currentEntity, localPlayer))
								{
									if(boxF)
									{
										DrawEspBox2D(entityPosition2D.x, entityPosition2D.y, entityHead2D.x, entityHead2D.y, 1, D3DCOLOR_COLORVALUE(espColorVisibleF[0], espColorVisibleF[1], espColorVisibleF[2], 1.f));
									}
									if (healthF)
									{
										DrawHealth(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->iHealth);
									}
									if (armorF)
									{
										DrawArmor(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->armorValue);
									}
								}
								else if (!espVisibleOnlyF)
								{
									if (boxF)
									{
										DrawEspBox2D(entityPosition2D.x, entityPosition2D.y, entityHead2D.x, entityHead2D.y, 1, D3DCOLOR_COLORVALUE(espColorHiddenF[0], espColorHiddenF[1], espColorHiddenF[2], 1.f));
									}
									if (healthF)
									{
										DrawHealth(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->iHealth);
									}
									if (armorF)
									{
										DrawArmor(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->armorValue);
									}
								}
							}
						}

						if (snaplinesF)
						{
							if (!hack->IsEnemy(currentEntity, localPlayer))
							{
								if (hack->IsVisible(currentEntity, localPlayer))
								{
									DrawSnaplines(entityPosition2D.x, entityPosition2D.y, D3DCOLOR_COLORVALUE(snaplinesColorVisibleF[0], snaplinesColorVisibleF[1], snaplinesColorVisibleF[2], 1.f));
								}
								else if (!snaplinesVisibleOnlyF)
								{
									DrawSnaplines(entityPosition2D.x, entityPosition2D.y, D3DCOLOR_COLORVALUE(snaplinesColorHiddenF[0], snaplinesColorHiddenF[1], snaplinesColorHiddenF[2], 1.f));
								}
							}

						}
					}
					else
					{
						//ENEMY TEAM FUNCTIONS
						if (espE)
						{
							if (hack->WorldToScreen(entityHead3D, entityHead2D))
							{
								if (hack->IsVisible(currentEntity, localPlayer))
								{
									if (boxE)
									{
										DrawEspBox2D(entityPosition2D.x, entityPosition2D.y, entityHead2D.x, entityHead2D.y, 1, D3DCOLOR_COLORVALUE(espColorVisibleE[0], espColorVisibleE[1], espColorVisibleE[2], 1.f));
									}
									if (healthE)
									{
										DrawHealth(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->iHealth);
									}
									if (armorE)
									{
										DrawArmor(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->armorValue);
									}
								}
								else if (!espVisibleOnlyE)
								{
									if (boxE)
									{
										DrawEspBox2D(entityPosition2D.x, entityPosition2D.y, entityHead2D.x, entityHead2D.y, 1, D3DCOLOR_COLORVALUE(espColorHiddenE[0], espColorHiddenE[1], espColorHiddenE[2], 1.f));
									}
									if (healthE)
									{
										DrawHealth(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->iHealth);
									}
									if (armorE)
									{
										DrawArmor(entityPosition2D.x, entityPosition2D.y, entityHead2D.y, 3, currentEntity->armorValue);
									}
								}
							}
						}
						if (snaplinesE)
						{
							if (hack->IsEnemy(currentEntity, localPlayer))
							{
								if (hack->IsVisible(currentEntity, localPlayer))
								{
									DrawSnaplines(entityPosition2D.x, entityPosition2D.y, D3DCOLOR_COLORVALUE(snaplinesColorVisibleE[0], snaplinesColorVisibleE[1], snaplinesColorVisibleE[2], 1.f));
								}
								else if (!snaplinesVisibleOnlyE)
								{
									DrawSnaplines(entityPosition2D.x, entityPosition2D.y, D3DCOLOR_COLORVALUE(snaplinesColorHiddenE[0], snaplinesColorHiddenE[1], snaplinesColorHiddenE[2], 1.f));
								}
							}
						}
					}
				}
				//crosshair
				if (crosshair && !crossHairStatic)
				{
					hack->crosshair2D.x = windowWidth / 2;
					hack->crosshair2D.y = windowHeight / 2;
					DrawCrosshair();
				}
				else if (crosshair && crossHairStatic)
				{
					if (localPlayer->shotsFired > 0)
					{
						Vec3 punchAngle = hack->localEntity->aimPunchAngle;
						hack->crosshair2D.x = windowWidth / 2 - (windowWidth / 90 * punchAngle.y);
						hack->crosshair2D.y = windowHeight / 2 + (windowHeight / 90 * punchAngle.x);
					}
					else
					{
						hack->crosshair2D.x = windowWidth / 2;
						hack->crosshair2D.y = windowHeight / 2;
					}
					DrawCrosshair();
				}
			}
		}
	}
	originalEndScene(pDevice);
}

DWORD WINAPI HackThread(HMODULE hModule)
{

	if (GetD3D9Device(d3d9Device, sizeof(d3d9Device)))
	{
		memcpy(EndSceneBytes, (char*)d3d9Device[42], 7); //d3d9Device[42] = EndScene
		originalEndScene = (tEndScene)TrampolineHook((char*)d3d9Device[42], (char*)hkEndScene, 7);
	}

	hack = new Hack();
	hack->Init();

	while (!GetAsyncKeyState(VK_END) & 1)
	{
		hack->Update();
	}
	d3d9gui::Destroy();
	Patch((BYTE*)d3d9Device[42], EndSceneBytes, 7);
	FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(const HMODULE hModule, const uintptr_t reason, const void* reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	}
	return true;
}