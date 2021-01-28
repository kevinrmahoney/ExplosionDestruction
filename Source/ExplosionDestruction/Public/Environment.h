// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
class EXPLOSIONDESTRUCTION_API Environment
{
public:
	Environment();
	~Environment();

#define COLLISION_WEAPON	ECC_GameTraceChannel1

// This is used to declare CVARs
#define DECLARE_CVAR(Type, Name) \
static Type Name; \

	DECLARE_CVAR(int32, DebugWeapons)

	DECLARE_CVAR(int32, DebugLogs)

	DECLARE_CVAR(int32, DebugVerbosity)
};
