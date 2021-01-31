// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDCheckpoint.generated.h"

class UBoxComponent;
class AEDGameMode;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDCheckpoint();

	UFUNCTION(BlueprintCallable)
	int GetCheckpointNumber();

	// Define what the less than symbol means for this class
	FORCEINLINE bool operator<(AEDCheckpoint& OtherCheckpoint);

protected:

	// Overlap box
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPaperFlipbookComponent* Sprite;

	// Animation for door opening
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DoorOpeningAnimation;

	// The sprites to indicate the door being locked, unlocked or open
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DoorClosedAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* DoorOpenAnimation;

	// Depends on the map, where this checkpoint is along the level (start at 0)
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CheckpointNumber = 0;

	// If the player has touched this spawnpoint yet.
	bool HasTouched = false;

	// If the player can respawn at this checkpoint
	bool CanRespawnAt = true;

	// Save a pointer to the ED game mode - we'll be calling it multiple times
	AEDGameMode* GameMode;

	// Timer for waiting till door open animation is done
	FTimerHandle DoorOpeningTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Events
	UFUNCTION()
	void OnCheckpointBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOpeningAnimationDone();

	// Blueprintfuncton for when begin opening door
	UFUNCTION(BlueprintImplementableEvent)
	void EDOnOpenBegin();

	// Blueprintfuncton for when we end opening door
	UFUNCTION(BlueprintImplementableEvent)
	void EDOnOpenEnd();

};
