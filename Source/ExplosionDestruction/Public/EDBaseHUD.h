// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EDBaseHUD.generated.h"

class AEDCharacter;

/**
 *
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API UEDBaseHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCharacter(AEDCharacter* Character);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool Update();


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool Remove();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEDCharacter* Character;
};
