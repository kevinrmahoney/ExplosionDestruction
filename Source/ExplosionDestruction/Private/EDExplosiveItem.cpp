// Fill out your copyright notice in the Description page of Project Settings.


#include "EDExplosiveItem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Environment.h"
#include "TimerManager.h"
#include "Logger.h"
#include "DrawDebugHelpers.h"
#include "EDFire.h"

// Sets default values
AEDExplosiveItem::AEDExplosiveItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComp->CanCharacterStepUpOn = ECB_Yes;
	SpriteComp->SetCollisionProfileName(TEXT("Explosive"));
	SetRootComponent(SpriteComp);

	// Explosves have radial force component to them.
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Comp"));

	if(!RadialForceComp)
		Logger::Error(TEXT("Failed to create radial force component for explosive!"));
	else
		RadialForceComp->SetupAttachment(SpriteComp);
}

// Called when the game starts or when spawned
void AEDExplosiveItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEDExplosiveItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AEDExplosiveItem::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if(DamageAmount > 0.f)
	{
		Explode();

		AEDFire* Fire = Cast<AEDFire>(DamageCauser);

		if(Fire)
		{
			Fire->AddFuel(Fuel);
		}

		Destroy();
	}

	return 0.f;
}

void AEDExplosiveItem::Explode()
{
	// If we have knockback enabled, fire an impulse
	if(CausesKnockback)
	{
		RadialForceComp->FireImpulse();
	}

	// Apply explosive damage to those caught in the explosion radius
	ApplyExplosiveDamage();

	// Spawn the explosion effect
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, GetActorLocation(), GetActorRotation());

	// Draw the radius of the explosin on screen.
	if(Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), RadialForceComp->GetComponentLocation(), BlastRadius, 12, FColor::White, false, 1.f, 0, 3.f);
	}

	EDOnExplode();
}

void AEDExplosiveItem::ApplyExplosiveDamage()
{
	float ActualDamage = Damage;
	FVector BlastLocation = GetActorLocation();

	// Draw the actual blast radius to the world, and half of the radius too.
	if(Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), BlastLocation, BlastRadius / 2, 12, FColor::Red, false, .5, 0, 3.f);
		DrawDebugSphere(GetWorld(), BlastLocation, BlastRadius, 12, FColor::Yellow, false, .5, 0, 3.f);
	}

	/// We perform damage calculation two steps: once for the shooter, and once for everyone else.

	// 1. Apply damage to actors in the vicinity (excluding the Owner)
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());

	// Apply the damage
	UGameplayStatics::ApplyRadialDamageWithFalloff(
		GetWorld(),
		ActualDamage,
		ActualDamage / 2,
		GetActorLocation(),
		BlastRadius / 2,
		BlastRadius,
		1.f,
		nullptr,
		IgnoredActors,
		this,
		this->GetInstigatorController(),
		COLLISION_WEAPON);


	// 2. Apply damage to the owner if in vicinity
	TArray<FHitResult> OutHits;
	FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(BlastRadius);

	// Empty ignored actors list (used this array before so make sure its empty)
	IgnoredActors.Empty();

	// To a sweep to determine what we hit
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, BlastLocation, BlastLocation, FQuat::Identity, COLLISION_WEAPON, ExplosionSphere);

	// If we got hits
	if(isHit)
	{
		// For each actor that was hit, add the actor to ignored actors as long as they aren't the owner of this
		for(auto& Result : OutHits)
		{
			AActor* HitActor = Result.GetActor();
			if(HitActor && HitActor != GetOwner())
			{
				IgnoredActors.Add(HitActor);
			}
		}

		// Apply the damage to the people who were hit that were not the creator of the owner of this projectile
		UGameplayStatics::ApplyRadialDamageWithFalloff(
			GetWorld(),
			ActualDamage,
			ActualDamage / 2,
			GetActorLocation(),
			BlastRadius / 2,
			BlastRadius,
			1.f,
			nullptr,
			IgnoredActors,
			this,
			this->GetInstigatorController(),
			COLLISION_WEAPON);
	}
}