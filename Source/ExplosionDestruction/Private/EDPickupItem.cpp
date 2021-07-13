// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPickupItem.h"

// Sets default values
AEDPickupItem::AEDPickupItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEDPickupItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEDPickupItem::Activate()
{
	EDOnActivated();
}

