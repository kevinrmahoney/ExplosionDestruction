// Fill out your copyright notice in the Description page of Project Settings.


#include "EDExplosive.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Environment.h"
#include "TimerManager.h"
#include "Logger.h"
#include "DrawDebugHelpers.h"


AEDExplosive::AEDExplosive()
{
	// Explosves have radial force component to them.
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Comp"));

	if(!RadialForceComp)
		Logger::Fatal(TEXT("Failed to create radial force component for explosive!"));
	else
		RadialForceComp->SetupAttachment(SpriteComp);
	
	/* Settings for explosives. Copy + paste these to new explosive sublcasses
	
	// Explosive properties
	BlastRadius = 300.f;
	CausesKnockback = true;

	RadialForceComp->Radius = 300.f;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->ImpulseStrength = 100.f;
	RadialForceComp->ForceStrength = 0.f; // we aren't using the force
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
	*/
}

void AEDExplosive::BeginPlay()
{
	Super::BeginPlay();
}

void AEDExplosive::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	// If we have a direct hit
	if(OtherActor == GetOwner() && HitShooter)
		ApplyDamage(OtherActor, Hit);
	if(OtherActor != GetOwner() && HitOthers)
		ApplyDamage(OtherActor, Hit);

	// If we should destroy on hit, otherwise just collide.
	if(DestroyOnHit)
	{
		Destroy();
	}
	if(Hit.bBlockingHit)
	{
		EDOnCollide();
	}
}

void AEDExplosive::Destruct(AActor* Actor)
{
	// First, explode
	Explode();

	// Call super method after (so we dont destroy ourselves before exploding).
	Super::Destruct(Actor);
}

void AEDExplosive::Destruct()
{
	Destruct(this);
}

void AEDExplosive::Explode()
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

void AEDExplosive::ApplyExplosiveDamage()
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

	// Calculate the damage for hitting the owner (the person who shot)
	ActualDamage *= SelfDamageScale;

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