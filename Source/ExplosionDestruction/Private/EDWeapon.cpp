// Fill out your copyright notice in the Description page of Project Settings.


#include "EDWeapon.h"
#include "Logger.h"
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
	PRINTFUNC
	// Get the person shooting the weapon and their location
	AActor* Shooter = GetOwner();
	FVector ActorLocation = Shooter->GetActorLocation();
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	FVector TraceEnd;

	ActorLocation.Y = 0.f;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
	MouseWorldLocation.Y = 0.f;
	TraceEnd = (MouseWorldLocation - ActorLocation) * 10000 + ActorLocation;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Shooter);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FVector TraceEndPoint = TraceEnd;
	FHitResult Hit;
	if(GetWorld()->LineTraceSingleByChannel(Hit, ActorLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		// calculate damage
		AActor* HitActor = Hit.GetActor();

		UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, Shooter->GetActorRotation().Vector(), Hit, Shooter->GetInstigatorController(), this, nullptr);
	}

	DrawDebugLine(GetWorld(), ActorLocation, TraceEnd, FColor::Red, false, 0.5f, 0, 5.f);
}

bool AEDWeapon::CanShoot()
{
	PRINTFUNC
	return CooldownProgress > Cooldown && Ammo > 0.f && GetOwner() && GetWorld();
}

bool AEDWeapon::PullTrigger()
{
	PRINTFUNC
	IsTriggerPulled = true;

	if(CanShoot())
	{
		Shoot();
		return true;
	}

	return false;
}

bool AEDWeapon::ReleaseTrigger()
{
	PRINTFUNC
	IsTriggerPulled = false;

	return true;
}

bool AEDWeapon::GetIsTriggerPulled()
{
	PRINTFUNC
	return IsTriggerPulled;
}