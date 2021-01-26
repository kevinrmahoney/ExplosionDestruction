// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EDPlayerStart.h"
#include "EDGameMode.generated.h"

class AEDPlayerController;
class AEDCharacter;

/**
 * The GameMode defines the game being played. It governs the game rules, scoring, what actors
 * are allowed to exist in this game type, and who may enter the game.
 *
 * This game mode just sets the default pawn to be the MyCharacter asset, which is a subclass of ExplosionDestructionCharacter
 */
UCLASS(minimalapi)
class AEDGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AEDGameMode();

    // Spawn a new character and allow the controller to possess
    bool SpawnCharacter(AEDPlayerController* Controller);

    // Kill a player's character
    bool KillPlayerCharacter(AEDPlayerController* Controller);

    UFUNCTION(BlueprintCallable)
    float GetTimer();

protected:
    virtual void Tick(float DeltaSeconds) override;
    virtual void BeginPlay() override;

    float Timer;

    // This is the class we should spawn for characters
    UPROPERTY(EditAnywhere, Category = "Spawnable Characters")
    TSubclassOf<class AEDCharacter> CharacterClass;

    // The specific spawn point type we should find in the map
    UPROPERTY(EditAnywhere, Category = "Spawn Point")
    TSubclassOf<class AEDPlayerStart> SpawnPointClass;

    // An array of spawn points to reference
    TArray<AActor*> SpawnPoints;

};
