// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPlayerController : public APlayerController
{
	GENERATED_BODY()

	void SetupInputComponent() override;

	void ShootPressed();

	void ShootReleased();

	void Move(float Movement);

	void JumpPressed();

	void JumpReleased();
	
};
