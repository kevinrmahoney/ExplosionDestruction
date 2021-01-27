// Copyright Epic Games, Inc. All Rights Reserved.

#include "EDGameMode.h"
#include "EDCharacter.h"
#include "EDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"
#include "EDPlayerStart.h"

AEDGameMode::AEDGameMode()
{
	// Set default pawn class to our character
	DefaultPawnClass = AEDCharacter::StaticClass();
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
}

void AEDGameMode::BeginPlay()
{
	Super::BeginPlay();
	// Find all spawn points and put in array.
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnPointClass.Get(), SpawnPoints);
}

void AEDGameMode::Tick(float DeltaSeconds)
{
	// Keep track of how much time has passed in this particular run.
	Super::Tick(DeltaSeconds);
	Timer += DeltaSeconds;
}

bool AEDGameMode::KillPlayerCharacter(AEDPlayerController* Controller)
{
	// If we have the controller, get the controlled pawn and cast it to an EDCharacter
	if(Controller)
	{
		AEDCharacter* Char = Cast<AEDCharacter>(Controller->GetPawn());

		// Unpossess the character and destroy it
		if(Char)
		{
			Controller->UnPossess();
			Char->Destroy();
			return true;
		}
	}

	return false;
}

bool AEDGameMode::SpawnCharacter(AEDPlayerController* Controller)
{
	AEDCharacter* SpawnedCharacter;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Controller;
	AActor** SpawnPoint;

	// Get spawn points and reset the timer
	SpawnPoint = SpawnPoints.GetData();
	Timer = 0;

	// Make sure there are no nulls, then spawn the actor
	if(GetWorld() && SpawnPoint && *SpawnPoint)
	{
		SpawnedCharacter = GetWorld()->SpawnActor<AEDCharacter>(CharacterClass, (*SpawnPoint)->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

		// If we successfully spawned the actor, the controller should possess the newly spawned character
		if(SpawnedCharacter)
		{
			if(Controller)
			{
				Controller->Possess(SpawnedCharacter);
				return true;
			}
		}
	}

	return false;
}

float AEDGameMode::GetCurrentTime()
{
	return Timer;
}

float AEDGameMode::GetBestTime()
{
	return BestTime;
}

bool AEDGameMode::CheckTime(float Time)
{
	if(BestTime == 0.f || Time < BestTime)
	{
		BestTime = Time;
		return true;
	}

	return false;
}