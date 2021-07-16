// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EDPlayerController.generated.h"

class AEDCharacter;
class AEDGameMode;

/**
 *
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

private:
	AEDCharacter* EDCharacter;

	bool PossessedIsEDCharacter = false;

	// Input Binds
	void ShootPressed();
	void ShootReleased();
	void MoveRightPressed();
	void MoveRightReleased();
	void MoveLeftPressed();
	void MoveLeftReleased();
	void JumpPressed();
	void JumpReleased();
	void SlidePressed();
	void SlideReleased();
	void RocketLauncherPressed();
	void GrenadeLauncherPressed();
	void AssaultRiflePressed();
	void RespawnPressed();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* NewPawn) override;

	virtual void OnUnPossess() override;

	void SetupInputComponent() override;

	AEDGameMode* EDGameMode;

};
