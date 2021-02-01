// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPowerup.h"

// Sets default values
AEDPowerup::AEDPowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PowerupInterval = 0.f;
	TotalNumberOfTicks = 0;
}

// Called when the game starts or when spawned
void AEDPowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEDPowerup::OnTickPowerup()
{
	TicksProcessed++;

	EDOnPowerupTicked();
	if (TicksProcessed >= TotalNumberOfTicks)
	{
		EDOnExpired();

		GetWorldTimerManager().ClearTimer(TimerHandle_PowerupTick);
	}
}

void AEDPowerup::ActivatePowerup()
{
	EDOnActivated();
	if (PowerupInterval > 0.f)
	{
		GetWorldTimerManager().SetTimer(TimerHandle_PowerupTick, this, &AEDPowerup::OnTickPowerup, PowerupInterval, true, 0.f);
	}
	else
	{
		OnTickPowerup();
	}
}

void AEDPowerup::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

