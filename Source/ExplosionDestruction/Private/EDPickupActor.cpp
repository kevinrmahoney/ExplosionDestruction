// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPickupActor.h"
#include "Components/SphereComponent.h"
#include "EDPowerup.h"
#include "EDCharacter.h"

// Sets default values
AEDPickupActor::AEDPickupActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetSphereRadius(30.f);
	RootComponent = SphereComp;

	
}

// Called when the game starts or when spawned
void AEDPickupActor::BeginPlay()
{
	Super::BeginPlay();
	
	Respawn();
}

void AEDPickupActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (PickupInstance && Cast<AEDCharacter>(OtherActor))
	{
		PickupInstance->Activate();
		PickupInstance = nullptr;

		GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &AEDPickupActor::Respawn, CooldownDuration);
	}
}

void AEDPickupActor::Respawn()
{
	if (!PickupClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Pickup class not set in %s!"), *GetName());
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	PickupInstance = GetWorld()->SpawnActor<AEDPickupItem>(PickupClass, GetTransform(), SpawnParams);

	// check if any actors are overlapping on respawn, call activation method for first actor instance
	TArray<AActor*> OutActors;
	GetOverlappingActors(OutActors, AEDCharacter::StaticClass());
	AActor** OverlappingActor = OutActors.GetData();
	if (OverlappingActor && *OverlappingActor)
	{
		NotifyActorBeginOverlap(*OverlappingActor);
	}
}
