// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDPickupActor.generated.h"

class USphereComponent;
class AEDPowerup;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDPickupActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEDPickupActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "PickupActor")
	TSubclassOf<AEDPowerup> PowerupClass;

	AEDPowerup* PowerupInstance;

	UPROPERTY(EditDefaultsOnly, Category = "PickupActor")
	float CooldownDuration;

	FTimerHandle TimerHandle_RespawnTimer;

	void Respawn();

public:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

