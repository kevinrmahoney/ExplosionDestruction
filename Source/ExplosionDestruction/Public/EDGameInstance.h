// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EDGameInstance.generated.h"

/**
 *
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API UEDGameInstance : public UGameInstance
{
	GENERATED_BODY()

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

};
