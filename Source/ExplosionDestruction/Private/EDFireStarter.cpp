// Fill out your copyright notice in the Description page of Project Settings.


#include "EDFireStarter.h"
#include "EDFire.h"
#include "Logger.h"

// Sets default values
AEDFireStarter::AEDFireStarter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Area"));
	TriggerArea->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AEDFireStarter::BeginPlay()
{
	Super::BeginPlay();

	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AEDFireStarter::OnTriggerAreaBeginOverlap);
}

// Called every frame
void AEDFireStarter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEDFireStarter::OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Logger::Info(TEXT("Triggered Fire '%s'"), *TriggeredFire->GetName());

	TriggeredFire->Start();
}