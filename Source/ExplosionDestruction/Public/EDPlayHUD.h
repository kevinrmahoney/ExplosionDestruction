// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EDPlayHUD.generated.h"

/**
 *
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPlayHUD : public AHUD
{
	GENERATED_BODY()

	AEDPlayHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

};
