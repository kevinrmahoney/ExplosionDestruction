// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

// Widget includes
#include "EDHealthBar.h"
#include "EDAmmoCount.h"
#include "EDSpedometer.h"

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

protected:

	/* Widgets */

	// Health Widget
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UEDHealthBar> HealthBarClass;
	class UEDHealthBar* HealthWidget;

	// Ammo Widget
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UEDAmmoCount> AmmoCountClass;
	class UEDAmmoCount* AmmoCountWidget;

	// Spedometer Widget
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UEDSpedometer> SpedometerClass;
	class UEDSpedometer* SpedometerWidget;


	/* Variables to draw values from to fill in HUD */
	UPROPERTY(BlueprintReadOnly)
	AEDCharacter* Character;
	
};
