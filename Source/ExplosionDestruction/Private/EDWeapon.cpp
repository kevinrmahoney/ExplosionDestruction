// Fill out your copyright notice in the Description page of Project Settings.


#include "EDWeapon.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEDWeapon::AEDWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	RootComponent = SpriteComp;
}

void AEDWeapon::Tick(float DeltaSeconds)
{
	CooldownProgress += DeltaSeconds;
}

void AEDWeapon::Shoot()
{
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		FVector ActorLocation = MyOwner->GetActorLocation();
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		FVector TraceEnd;
		ActorLocation.Y = 0.f;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		MouseWorldLocation.Y = 0.f;
		TraceEnd = (MouseWorldLocation - ActorLocation) * 10000 + ActorLocation;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;
		QueryParams.bReturnPhysicalMaterial = true;

		FVector TraceEndPoint = TraceEnd;
		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, TraceEnd, ECC_Visibility, QueryParams))
		{
			// calculate damage
			AActor* HitActor = Hit.GetActor();

			UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, MyOwner->GetActorRotation().Vector(), Hit, MyOwner->GetInstigatorController(), this, nullptr);
		}

		DrawDebugLine(GetWorld(), ActorLocation, TraceEnd, FColor::Red, false, 0.5f, 0, 5.f);
	}

	CooldownProgress = 0.f;
}
