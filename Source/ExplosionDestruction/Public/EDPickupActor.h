// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDPickupActor.generated.h"

class USphereComponent;
class AEDPickupItem;

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

	UPROPERTY(EditAnywhere, Category = "PickupActor")
	USphereComponent* SphereComp;

	UPROPERTY(EditAnywhere, Category = "PickupActor")
	TSubclassOf<AEDPickupItem> PickupClass;

	AEDPickupItem* PickupInstance;

	UPROPERTY(EditAnywhere, Category = "PickupActor")
	float CooldownDuration;

	FTimerHandle TimerHandle_RespawnTimer;

	void Respawn();

public:

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};

