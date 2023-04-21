#pragma once
#include "main.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct { unsigned char MAKE_PAD(offset); type name; }

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

class Entity
{
public:
	union
	{
		DEFINE_MEMBER_N(bool, isDormant, 0xED);
		DEFINE_MEMBER_N(int, iHealth, 0x100);
		DEFINE_MEMBER_N(Vec3, vecViewOfs, 0x108);
		DEFINE_MEMBER_N(Vec3, vecOrigin, 0x138);
		DEFINE_MEMBER_N(int, iTeamNumber, 0xF4);
		DEFINE_MEMBER_N(int, boneMatrix, 0x26A8);
		DEFINE_MEMBER_N(int, armorValue, 0x117CC);
		DEFINE_MEMBER_N(Vec3, aimPunchAngle, 0x303C);
		DEFINE_MEMBER_N(int, shotsFired, 0x103E0);
	};
};

class EntityListObject
{
public:
	Entity* entity;
	char padding[12];
};

class EntityList
{
public:
	EntityListObject entities[32];
};

class Hack
{
public:
	uintptr_t engine;
	uintptr_t client;

	Entity* localEntity;
	EntityList* entityList;

	float viewMatrix[16];

	ID3DXLine* lineL;

	Vec2 crosshair2D;
	int crosshairSize = 6;

	Vec3 myPos;
	Vec3 delta;
	float deltaSquareRoot = NULL;
	float pitch;
	float yaw;
	float distance = NULL;

	void Init();
	void Update();
	bool CheckValidEntity(Entity* entity);
	bool WorldToScreen(Vec3 position, Vec2& screen);
	Vec3 GetBonePosition(Entity* entity, int bone);
	void GetMyCrosshairPos(Entity* localEntity, Vec3& myPos);

	bool IsEnemy(Entity* entity, Entity* localEntity);
	bool IsVisible(Entity* entity, Entity* localEntity);
	Entity* GetClosestToPlayer(Entity* entity, Entity* localEntity);
	bool GetClosestToCrosshair(Vec2 entityHead2D);
	void UseAimbot(Entity* entity);


};