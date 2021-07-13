// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDPickupItem.generated.h"

/**
 * Do not make objects from this class, please inherit from it
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPickupItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDPickupItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Activate();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup", meta = (DisplayName = "On Activated"))
	void EDOnActivated();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup", meta = (DisplayName = "On Expired"))
	void EDOnExpired();
};
