#pragma once

enum Bones
{
	head,
	neck,
	body,
	legs,
	feet,
	nearest
};

//Visuals General
inline bool enableVisuals = true;
inline bool crosshair = false;
inline bool crossHairStatic = false;

//Visuals Friend
inline bool chamsF = false;
inline bool chamsVisibleOnlyF = false;
inline bool espF = false;
inline bool espVisibleOnlyF = false;
inline bool snaplinesF = false;
inline bool snaplinesVisibleOnlyF = false;
inline float chamsColorVisibleF[] = { 0.3765f, 0.6745f, 1.f };
inline float chamsColorHiddenF[] = { 0.9412f, 0.0f, 1.f };
inline float espColorVisibleF[] = { 0.3765f, 0.6745f, 1.f };
inline float espColorHiddenF[] = { 0.9412f, 0.0f, 1.f };
inline float snaplinesColorVisibleF[] = { 0.3765f, 0.6745f, 1.f };
inline float snaplinesColorHiddenF[] = { 0.9412f, 0.0f, 1.f };

inline bool boxF = true;
inline bool nameF = false;
inline bool healthF = false;
inline bool armorF = false;
inline bool weaponF = false;
inline bool ammoF = false;


//Visuals Enemy
inline bool chamsE = false;
inline bool chamsVisibleOnlyE = false;
inline bool espE = false;
inline bool espVisibleOnlyE = false;
inline bool snaplinesE = false;
inline bool snaplinesVisibleOnlyE = false;
inline float espColorVisibleE[] = { 1.f, 0.0f, 0.0f };
inline float espColorHiddenE[] = { 1.0f, 1.0f, 0.0f };
inline float chamsColorVisibleE[] = { 1.f, 0.0f, 0.0f };
inline float chamsColorHiddenE[] = { 1.0f, 1.0f, 0.0f };
inline float snaplinesColorVisibleE[] = { 1.f, 0.0f, 0.0f };
inline float snaplinesColorHiddenE[] = { 1.0f, 1.0f, 0.0f };

inline bool boxE = true;
inline bool nameE = false;
inline bool healthE = false;
inline bool armorE = false;
inline bool weaponE = false;
inline bool ammoE = false;

//Visuals Weapon
inline bool espW = false;
inline bool espVisibleOnlyW = false;
inline bool chamsW = false;
inline bool chamsVisibleOnlyW = false;
inline bool snaplinesW = false;
inline bool snaplinesVisibleOnlyW = false;
inline float espColorVisibleW[] = { 0.3765f, 0.6745f, 1.f };
inline float espColorHiddenW[] = { 0.3765f, 0.6745f, 1.f };
inline float chamsColorVisibleW[] = { 0.3765f, 0.6745f, 1.f };
inline float chamsColorHiddenW[] = { 0.3765f, 0.6745f, 1.f };
inline float snaplinesColorVisibleW[] = { 0.3765f, 0.6745f, 1.f };
inline float snaplinesColorHiddenW[] = { 0.3765f, 0.6745f, 1.f };

inline bool boxW = true;
inline bool nameW = false;
inline bool ammoW = false;

//Aimbot
inline bool enableAimbot = false;
inline int aimbotKey = VK_LBUTTON;
inline float aimbotSmoothing = 0.0f;
inline int aimbotPosition = head;
inline bool aimEnemysOnly = true;
inline bool aimVisibleOnly = true;