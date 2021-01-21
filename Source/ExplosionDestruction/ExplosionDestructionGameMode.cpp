// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExplosionDestructionGameMode.h"
#include "ExplosionDestructionCharacter.h"

AExplosionDestructionGameMode::AExplosionDestructionGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AExplosionDestructionCharacter::StaticClass();	
}
