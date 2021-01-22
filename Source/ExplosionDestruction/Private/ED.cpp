// Copyright Epic Games, Inc. All Rights Reserved.

#include "EDGameMode.h"
#include "EDCharacter.h"

AEDGameMode::AEDGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AEDCharacter::StaticClass();	
}
