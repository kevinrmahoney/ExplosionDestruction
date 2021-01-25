// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EDSpedometer.generated.h"

class EDCharacter;

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API UEDSpedometer : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetCharacter(AEDCharacter* NewCharacter);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEDCharacter* Character;
	
};
