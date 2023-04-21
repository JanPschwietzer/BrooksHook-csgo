#pragma once
#include "hack.h"
#include "csgotrace.h"

#define M_PI 3.14159265359
#include <cmath>

tTraceRay TraceRay;
tCreateInterface CreateInterface;
IEngineTrace* engineTrace;

float CalculatePitch(float& z, float& deltaSquareRoot);
float CalculateYaw(float& y, float& x);

void Hack::Init()
{
	client = (uintptr_t)GetModuleHandle(L"client.dll");
	engine = (uintptr_t)GetModuleHandle(L"engine.dll");
	entityList = (EntityList*)(client + offsets::dwEntityList);
	localEntity = entityList->entities[0].entity;
	CreateInterface = (tCreateInterface)GetProcAddress((HMODULE)engine, "CreateInterface");
	engineTrace = (IEngineTrace*)GetInterface(CreateInterface, "EngineTraceClient004");
}
void Hack::Update()
{
	memcpy(&viewMatrix, (PBYTE*)(client + offsets::dwViewMatrix), sizeof(viewMatrix));
}
bool Hack::CheckValidEntity(Entity* entity)
{
	if (entity == nullptr)
		return false;
	if (entity == localEntity)
		return false;
	if (entity->iHealth <= 0)
		return false;
	if (entity->isDormant)
		return false;
	return true;
}

bool Hack::WorldToScreen(Vec3 position, Vec2& screen)
{
	Vec4 clipCoords;
	clipCoords.x = position.x * viewMatrix[0] +
		position.y * viewMatrix[1] +
		position.z * viewMatrix[2] +
		viewMatrix[3];
	clipCoords.y = position.x * viewMatrix[4] +
		position.y * viewMatrix[5] +
		position.z * viewMatrix[6] +
		viewMatrix[7];
	clipCoords.z = position.x * viewMatrix[8] +
		position.y * viewMatrix[9] +
		position.z * viewMatrix[10] +
		viewMatrix[11];
	clipCoords.w = position.x * viewMatrix[12] +
		position.y * viewMatrix[13] +
		position.z * viewMatrix[14] +
		viewMatrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vec3 ndc;
	ndc.x = clipCoords.x / clipCoords.w;
	ndc.y = clipCoords.y / clipCoords.w;

	screen.x = (windowWidth / 2 * ndc.x) + (ndc.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * ndc.y) + (ndc.y + windowHeight / 2);
	return true;
}

Vec3 Hack::GetBonePosition(Entity* entity, int bone)
{
	uintptr_t bonePtr = entity->boneMatrix;
	Vec3 bonePos;
	bonePos.x = *(float*)(bonePtr + 0x30 * bone + 0x0C); // TODO?
	bonePos.y = *(float*)(bonePtr + 0x30 * bone + 0x1C); // TODO?
	bonePos.z = *(float*)(bonePtr + 0x30 * bone + 0x2C); // TODO?
	return bonePos;
}

void Hack::GetMyCrosshairPos(Entity* localEntity, Vec3& myPos)
{
	myPos.x = localEntity->vecOrigin.x + localEntity->vecViewOfs.x;
	myPos.y = localEntity->vecOrigin.y + localEntity->vecViewOfs.y;
	myPos.z = localEntity->vecOrigin.z + localEntity->vecViewOfs.z;
}

void Hack::UseAimbot(Entity* entity)
{
	if (!IsEnemy(entity, localEntity))
		return;

	uintptr_t engine = (uintptr_t)GetModuleHandle(L"engine.dll");
	Vec3* viewAngles = (Vec3*)(*(uintptr_t*)(engine + offsets::dwViewMatrix) + offsets::dwClientState_ViewAngles);
	Vec3 enemyPos = GetBonePosition(entity, 8);
	GetMyCrosshairPos(localEntity, myPos);

	delta = Vec3(enemyPos.x - myPos.x,
		enemyPos.y - myPos.y,
		enemyPos.z - myPos.z);
	deltaSquareRoot = sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);

	pitch = CalculatePitch(delta.z, deltaSquareRoot);
	yaw = CalculateYaw(delta.y, delta.x);

	viewAngles->x = pitch - localEntity->aimPunchAngle.x;
	viewAngles->y = yaw + localEntity->aimPunchAngle.y;
}

float CalculatePitch(float& z, float& deltaSquareRoot)
{
	return -asin(z / deltaSquareRoot) * (180 / M_PI);
}

float CalculateYaw(float& y, float& x)
{
	return atan2(y, x) * (180 / M_PI);
}

bool Hack::GetClosestToCrosshair(Vec2 entityHead2D)
{
	if (distance == NULL)
	{
		distance = fabs(crosshair2D.x - entityHead2D.x) * fabs(crosshair2D.x - entityHead2D.x) + fabs(crosshair2D.y - entityHead2D.y) * fabs(crosshair2D.y - entityHead2D.y);
		return true;
	}

	float newDistance = fabs(crosshair2D.x - entityHead2D.x) * fabs(crosshair2D.x - entityHead2D.x) + fabs(crosshair2D.y - entityHead2D.y) * fabs(crosshair2D.y - entityHead2D.y);
	if (distance > newDistance)
	{
		distance = newDistance;
		return true;
	}
	return false;
}

bool Hack::IsEnemy(Entity* entity, Entity* localEntity)
{
	if (entity->iTeamNumber == localEntity->iTeamNumber)
		return false;
	return true;
}
bool Hack::IsVisible(Entity* entity, Entity* localEntity)
{
	Vec3 enemyPos = {};
	GetMyCrosshairPos(localEntity, myPos);
	GetMyCrosshairPos(entity, enemyPos);

	CGameTrace trace;
	Ray_t ray;
	CTraceFilter tracefilter;
	tracefilter.pSkip = (void*)localEntity;

	ray.Init(vec3(myPos.x, myPos.y, myPos.z), vec3(enemyPos.x, enemyPos.y, enemyPos.z));

	engineTrace->TraceRay(ray, MASK_SHOT | CONTENTS_GRATE, &tracefilter, &trace);

	if (entity == trace.hit_entity)
		return true;
	return false;
}