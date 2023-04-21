#include "gui.h"

#include <string>

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

bool d3d9gui::SetupWindowClass(const char* windowClassName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = DefWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandle(NULL); //current Process
	windowClass.hIcon = NULL;
	windowClass.hCursor = NULL;
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = (LPCWSTR) windowClassName;
	windowClass.hIconSm = NULL;

	if (!RegisterClassEx(&windowClass))
		return false;
	return true;
}
void d3d9gui::DestroyWindowClass() noexcept
{
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool d3d9gui::SetupWindow(const char* windowName) noexcept
{
	window = CreateWindow(windowClass.lpszClassName, (LPCWSTR) windowName, WS_OVERLAPPEDWINDOW, 0, 0, 100, 100, 0, 0, windowClass.hInstance, 0);

	if (!window)
		return false;
	return true;
}
void d3d9gui::DestroyWindow() noexcept
{
	if (window)
		DestroyWindow(window);
}

void d3d9gui::SetupDevice(LPDIRECT3DDEVICE9 pDevice)
{
	if (!SetupWindowClass("imguimenu1337"))
		MessageBox(nullptr, L"Failed to create WindowClass", L"Error!", MB_OK);
	if (!SetupWindow("Imgui Menu"))
		MessageBox(nullptr, L"Failed to create Window", L"Error!", MB_OK);
	if (pDevice == nullptr)
	{
		MessageBox(nullptr, L"Failed to setup DirectX", L"Error!", MB_OK);
		return;
	}
	DestroyWindow();
	DestroyWindowClass();
}

void d3d9gui::SetupMenu(LPDIRECT3DDEVICE9 device) noexcept
{
	auto params = D3DDEVICE_CREATION_PARAMETERS { };
	device->GetCreationParameters(&params);
	window = params.hFocusWindow;

	originalWindowProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WindowProcess);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
	isSetup = true;
}
void d3d9gui::Destroy() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)originalWindowProc);
}
void d3d9gui::Render() noexcept
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	/*
	 *		MENUUU!!!
	 */

	ImGui::Begin("Brooks Hook D3D", &isOpen);

	if (ImGui::BeginTabBar("tabs"))
	{

		//VISUALS TAB
		if(ImGui::BeginTabItem("Visuals"))
		{
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("General Settings");
			ImGui::Spacing();
			ImGui::Checkbox("Enable Visuals", &enableVisuals);
			ImGui::Checkbox("Show Crosshair", &crosshair);
			ImGui::Checkbox("Show Recoil", &crossHairStatic);
			ImGui::Spacing();
			ImGui::Separator();
			ImGui::Columns(3, "visual_columns", false);

			//FriendVisuals
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Friends");
			ImGui::Spacing();
			ImGui::Checkbox("Chams##Friendly", &chamsF);
			if (chamsF)
			{
				ImGui::Checkbox("Only Visible##FriendlyChams", &chamsVisibleOnlyF);
				ImGui::ColorEdit3("Visible##chamsFriendly", chamsColorVisibleF);
				ImGui::ColorEdit3("Hidden##chamsFriendly", chamsColorHiddenF);
			}
			ImGui::Checkbox("ESP##Friendly", &espF);
			if (espF)
			{
				ImGui::Checkbox("Only Visible##FriendlyESP", &espVisibleOnlyF);
				ImGui::Checkbox("Box##Friendly", &boxF);
				ImGui::Checkbox("Name##Friendly", &nameF);
				ImGui::Checkbox("Health##Friendly", &healthF);
				ImGui::Checkbox("Armor##Friendly", &armorF);
				ImGui::Checkbox("Weapon##Friendly", &weaponF);
				ImGui::Checkbox("Ammo##Friendly", &ammoF);
				ImGui::ColorEdit3("Visible##ESPFriendly", espColorVisibleF);
				ImGui::ColorEdit3("Hidden##ESPFriendly", espColorHiddenF);
			}
			ImGui::Checkbox("Snaplines##Friendly", &snaplinesF);
			if (snaplinesF)
			{
				ImGui::Checkbox("Only Visible##FriendlySnaplines", &snaplinesVisibleOnlyF);
				ImGui::ColorEdit3("Visible##snaplinesFriendly", snaplinesColorVisibleF);
				ImGui::ColorEdit3("Hidden##snaplinesFriendly", snaplinesColorHiddenF);
			}
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::NextColumn();

			//EnemyVisuals
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Enemies");
			ImGui::Spacing();
			ImGui::Checkbox("Chams##Enemy", &chamsE);
			if (chamsE)
			{
				ImGui::Checkbox("Only Visible##EnemyChams", &chamsVisibleOnlyE);
				ImGui::ColorEdit3("Visible", chamsColorVisibleE);
				ImGui::ColorEdit3("Hidden", chamsColorHiddenE);
			}
			ImGui::Checkbox("ESP##Enemy", &espE);
			if (espE)
			{
				ImGui::Checkbox("Only Visible##EnemyESP", &espVisibleOnlyE);
				ImGui::Checkbox("Box##Enemy", &boxE);
				ImGui::Checkbox("Name##Enemy", &nameE);
				ImGui::Checkbox("Health##Enemy", &healthE);
				ImGui::Checkbox("Armor##Enemy", &armorE);
				ImGui::Checkbox("Weapon##Enemy", &weaponE);
				ImGui::Checkbox("Ammo##Enemy", &ammoE);
				ImGui::ColorEdit3("Visible", espColorVisibleE);
				ImGui::ColorEdit3("Hidden", espColorHiddenE);
			}
			ImGui::Checkbox("Snaplines##Enemy", &snaplinesE);
			if (snaplinesE)
			{
				ImGui::Checkbox("Only Visible##EnemySnaplines", &snaplinesVisibleOnlyE);
				ImGui::ColorEdit3("Visible", snaplinesColorVisibleE);
				ImGui::ColorEdit3("Hidden", snaplinesColorHiddenE);
			}
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::NextColumn();

			//WeaponVisuals
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Weapons");
			ImGui::Spacing();
			ImGui::Checkbox("Chams##Weapon", &chamsW);
			if (chamsW)
			{
				ImGui::Checkbox("Only Visible##WeaponChams", &chamsVisibleOnlyW);
				ImGui::ColorEdit3("Visible", chamsColorVisibleW);
				ImGui::ColorEdit3("Hidden", chamsColorHiddenW);
			}
			ImGui::Checkbox("ESP##Weapon", &espW);
			if (espW)
			{
				ImGui::Checkbox("Only Visible##WeaponESP", &espVisibleOnlyW);
				ImGui::Checkbox("Box##Weapon", &boxW);
				ImGui::Checkbox("Name##Weapon", &nameW);
				ImGui::Checkbox("Ammo##Weapon", &ammoW);
				ImGui::ColorEdit3("Visible", espColorVisibleW);
				ImGui::ColorEdit3("Hidden", espColorHiddenW);
			}
			ImGui::Checkbox("Snaplines##Weapon", &snaplinesW);
			if (snaplinesW)
			{
				ImGui::Checkbox("Only Visible##WeaponSnaplines", &snaplinesVisibleOnlyW);
				ImGui::ColorEdit3("Visible", snaplinesColorVisibleW);
				ImGui::ColorEdit3("Hidden", snaplinesColorHiddenW);
			}
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Columns();
			ImGui::EndTabItem();
		}

		//AIMBOT
		if (ImGui::BeginTabItem("Aimbot"))
		{
			ImGui::Separator();
			ImGui::Text("General Settings");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &enableAimbot);
			//ImGui::ListBox("Aimbot Key");
			ImGui::Text("Aimbot Smoothing");
			ImGui::SliderFloat("##aimbot-slider", &aimbotSmoothing, 0.0f, 100.f);
			ImGui::Checkbox("Enemies only", &aimEnemysOnly);
			ImGui::Checkbox("Visible only", &aimVisibleOnly);

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		d3d9gui::isOpen = !d3d9gui::isOpen;

	if (d3d9gui::isOpen && ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
		return 1L;

	return CallWindowProc(d3d9gui::originalWindowProc, window, message, wParam, lParam);
}