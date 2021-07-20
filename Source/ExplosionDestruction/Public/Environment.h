// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class EXPLOSIONDESTRUCTION_API Environment
{
public:

#define COLLISION_WEAPON    ECC_GameTraceChannel1
#define ECC_Hitscan			ECC_GameTraceChannel8
#define ECC_Railgun         ECC_GameTraceChannel9

// This is used to declare CVARs
#define DECLARE_CVAR(Type, Name) \
static Type Name; \

	
/* All INIs declared below! Make sure to create a definition in the code file (Environment.cpp)! */

	// Logging
	DECLARE_CVAR(int32,     LogEnabled)
	DECLARE_CVAR(int32,     LogVerbosity)
	DECLARE_CVAR(int32,     LogToScreen)
	DECLARE_CVAR(int32,     LogShowTick)
	DECLARE_CVAR(int32,     LogShowTimestamp)

	// Cheats
	DECLARE_CVAR(int32,     InfiniteHealth)
	DECLARE_CVAR(int32,     PauseFire)

	// Debug
	DECLARE_CVAR(int32,     DebugFloorAngle)
	DECLARE_CVAR(int32,     DebugWeapons)
	DECLARE_CVAR(float,     DebugWeaponAlpha)
	DECLARE_CVAR(int32,     DebugHits)
	DECLARE_CVAR(int32,     DebugFire)
};
