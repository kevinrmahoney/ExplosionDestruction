// Copyright Epic Games, Inc. All Rights Reserved.

#include "EDGameMode.h"
#include "EDCharacter.h"
#include "EDPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"
#include "EDPlayerStart.h"
#include "EDCheckpoint.h"

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

	// Verify it has necessary fields set before starting, else cause a fatal error.
	if(!SpawnPointClass)
		Logger::Error(TEXT("Game mode has no spawn point class!"));

	if(!CheckpointClass)
		Logger::Error(TEXT("Game mode has no check point class!"));

	if(!CharacterClass)
		Logger::Error(TEXT("Game mode has no character class!"));
	
	FindCheckPoints();

	Logger::Info(TEXT("There are %d checkpoints on this map."), Checkpoints.Num());
}

void AEDGameMode::Tick(float DeltaSeconds)
{
	// Keep track of how much time has passed in this particular run.
	Super::Tick(DeltaSeconds);
	Timer += DeltaSeconds;
}

void AEDGameMode::FindCheckPoints()
{
	// Find all checkpoints and put in array.
	TArray<AActor*> TempCheckpointArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), CheckpointClass.Get(), TempCheckpointArray);

	AActor** TempCheckpointArrayStart = TempCheckpointArray.GetData();

	// If we couldnt a pointer to the array, or a pointer to the first element in 
	// the array of checkpoints, we should return early.
	if(!TempCheckpointArrayStart || !(*TempCheckpointArrayStart))
	{
		Logger::Error(TEXT("Could not find any checkpoints in level! Please add some!"));
		return;
	}
	else
	{
		Logger::Info(TEXT("Found %d check points on this map:"), TempCheckpointArray.Num());
	}

	// Empty the current checkpoint array and set the current first checkpoint to null
	Checkpoints.Empty();
	FirstCheckpoint = nullptr;

	// Add values from temp array to permanent one
	for(int i = 0; i < TempCheckpointArray.Num(); i++)
	{
		AActor* CheckpointArrayAtIndex = *TempCheckpointArrayStart;
		AEDCheckpoint* CheckpointToAdd = Cast<AEDCheckpoint>(CheckpointArrayAtIndex);
		Checkpoints.Add(CheckpointToAdd);

		// We save the first checkpoint for later use. Must start with 0.
		if(CheckpointToAdd->GetCheckpointNumber() == 0)
		{
			FirstCheckpoint = CheckpointToAdd;
		}

		Logger::Info(TEXT("Checkpoint #%d: %s"), CheckpointToAdd->GetCheckpointNumber(), *CheckpointToAdd->GetName());

		TempCheckpointArrayStart++;
	}

	// Sort the array based on their checkpoint number
	Checkpoints.Sort();

	// Find the first checkpoint in the array, and get its respawn point, and activate it.
	AEDCheckpoint** FirstCheckpointPointer = Checkpoints.GetData();
	FirstCheckpoint = *(FirstCheckpointPointer);

	if(FirstCheckpointPointer && FirstCheckpoint && FirstCheckpoint->GetRespawnPoint())
	{
		FirstCheckpoint->SetHasBeenReached(true);
		FirstCheckpoint->GetRespawnPoint()->Activate();
	}

	if(FirstCheckpoint == nullptr)
		Logger::Error(TEXT("Could not find a checkpoint with checkpoint to consider the first!"));
}

void AEDGameMode::CheckpointReached(AEDCheckpoint* Checkpoint)
{
	// Ignore if its the first checkpoint - simply spawning ontop of a checkpoint isnt worth celebrating over.
	if(FirstCheckpoint == Checkpoint)
		return;

	Logger::Screen(TEXT("Checkpoint %s reached in %f seconds."), *Checkpoint->GetName(), GetCurrentTime());

	if(GetCurrentTime() < GetBestTime() || GetBestTime() == 0.f)
	{
		BestTime = GetCurrentTime();
		Logger::Screen(TEXT("New session record!"));
		EDOnNewRecordBP();
	}
	else
	{
		EDOnCheckpontReachedBP();
	}

	Timer = 0.f;
}

AEDPlayerStart* AEDGameMode::GetFurthestSpawnPoint()
{
	AEDCheckpoint** CheckpointIterator = Checkpoints.GetData();
	AEDPlayerStart* LastSpawnPoint = nullptr;

	// We are looking for the last checkpoint that has been reached that has a spawn point
	// Go through the array backwards.
	for(int i = Checkpoints.Num() - 1; i >= 0; i--)
	{
		// Save the pointers to the checkpoint and its respawn point
		AEDCheckpoint* CheckpointAtIndex = *(CheckpointIterator+i);
		LastSpawnPoint = CheckpointAtIndex->GetRespawnPoint();

		// Check if it has a respawn point and if the checkpoint has been reached.
		if(CheckpointAtIndex && CheckpointAtIndex->HasBeenReached() && LastSpawnPoint)
		{
			Logger::Verbose(TEXT("Checkpoint %s with respawn point %s is the last one that the character reached."), *CheckpointAtIndex->GetName(), *LastSpawnPoint->GetName());
			return LastSpawnPoint;
		}
		// Otherwise, continue looking.
		else
		{
			LastSpawnPoint = nullptr;
			continue;
		}
	}

	Logger::Error(TEXT("Failed to find furthest spawn point that has been reached, in array with %d entries.\n\
							Make sure each checkpoint has an associated spawn point in the level, and each \n\
							checkpoint also has a checkpoint number set."), Checkpoints.Num());

	return nullptr;
}

bool AEDGameMode::KillPlayerCharacter(AEDPlayerController* Controller)
{
	AEDCharacter* Char;

	if(!Controller)
	{
		return false;
	}
	else
		Logger::Warning(TEXT("No controller provided - could not kill its character."));

	if(!Controller->GetPawn())
		Logger::Warning(TEXT("Controller %s controls no characters, so cannot kill the character."), *Controller->GetName());

	Char = Cast<AEDCharacter>(Controller->GetPawn());

	if(!Char)
	{
		Logger::Warning(TEXT("Casting controller %s character %s to EDCharacter failed"), *Controller->GetName(), *Controller->GetPawn()->GetName());
		return false;
	}

	// If we have the controller, get the controlled pawn and cast it to an EDCharacter
	// Unpossess the character and destroy it
	Controller->UnPossess();
	Char->Destroy();

	// Restart progress for this character.
	RestartGameMode();

	return true;
}

void AEDGameMode::RestartGameMode()
{
	AEDCheckpoint** FirstCheckpointPointer = Checkpoints.GetData();

	Timer = 0;

	// Go through each respawn point and reset it
	for(int i = 0; i < Checkpoints.Num(); i++)
	{
		AEDCheckpoint* Checkpoint = *(FirstCheckpointPointer + i);
		Checkpoint->Reset();

		// We always want one respawn point active, otherwise we cant respawn
		if(i == 0 && Checkpoint->GetRespawnPoint())
		{
			Checkpoint->GetRespawnPoint()->Activate();
			Checkpoint->SetHasBeenReached(true);
		}
	}
}

// We ty to spawn a new character at the furthest spawn point available.
bool AEDGameMode::SpawnCharacter(AEDPlayerController* Controller)
{
	if(!Controller)
	{
		Logger::Error(TEXT("Cannot spawn character for null controller!"));
		return false;
	}

	AEDCharacter* SpawnedCharacter = nullptr;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Controller;

	AEDPlayerStart* FurthestSpawnPoint = GetFurthestSpawnPoint();

	// Reset the timer
	Timer = 0.f;

	// Make sure there are no nulls, then spawn the actor
	if(GetWorld() && FurthestSpawnPoint)
	{
		SpawnedCharacter = GetWorld()->SpawnActor<AEDCharacter>(CharacterClass, FurthestSpawnPoint->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);

		// If we successfully spawned the actor, the controller should possess the newly spawned character
		if(SpawnedCharacter)
		{
			Controller->Possess(SpawnedCharacter);
			return true;
		}
		else
		{
			Logger::Error(TEXT("Failed to spawn new character for controller %s"), *Controller->GetName());
		}
	}
	else
	{
		Logger::Error(TEXT("Error occurred trying to find a place to spawn new character for controller %s"), *Controller->GetName());
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

