// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EDHealthBar.generated.h"

class AEDCharacter;

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API UEDHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCharacter(AEDCharacter* NewCharacter);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEDCharacter* Character;
	
};
