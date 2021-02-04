// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDPickupItem.h"
#include "EDPowerup.generated.h"

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPowerup : public AEDPickupItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDPowerup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	float PowerupInterval;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
	int32 TotalNumberOfTicks;

	int32 TicksProcessed;

	FTimerHandle TimerHandle_PowerupTick;

	UFUNCTION()
	void OnTickPowerup();

public:	

	void Activate() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Powerups", meta = (DisplayName = "On Powerup Ticked"))
	void EDOnPowerupTicked();
};
