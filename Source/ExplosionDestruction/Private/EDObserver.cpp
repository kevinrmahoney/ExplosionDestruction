// Fill out your copyright notice in the Description page of Project Settings.


#include "EDObserver.h"
#include "Logger.h"

// Sets default values
AEDObserver::AEDObserver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEDObserver::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEDObserver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Logger::AddTick();
}

