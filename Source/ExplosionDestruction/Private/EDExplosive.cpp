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
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("Radial Force Comp"));
	RadialForceComp->SetupAttachment(SpriteComp);

	// Initialize movement component
	//MovementComp->InitialSpeed = 300.f;
	//MovementComp->MaxSpeed = 300.f;
	//MovementComp->ProjectileGravityScale = 0.f;
	//MovementComp->Bounciness = 0.f;

	if(CausesKnockback)
	{
		RadialForceComp->Radius = BlastRadius;
		RadialForceComp->ImpulseStrength = KnockbackVelocity;
		RadialForceComp->ForceStrength = 0.f; // we aren't using the force
		RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
		RadialForceComp->bImpulseVelChange = true;
	}
	// Initialize variables

	// Blast
	//BlastRadius = 300.f;
	//BlastDamage = 50.f;
	//NoSelfDamage = false;
	//DamageModel = EMathematicalModel::Linear;

	// Knockback
	//CausesKnockback = true;
	//KnockbackVelocity = 2000.f;
	//MinKnockback = 100.f;
	//SelfKnockbackScale = 1.f;

	// Radial force component
}

void AEDExplosive::BeginPlay()
{
	Super::BeginPlay();

	// Initialize movement component
	//MovementComp->InitialSpeed = 1000.f;
	//MovementComp->MaxSpeed = 1000.f;
	//MovementComp->ProjectileGravityScale = 0.f;
	//MovementComp->Bounciness = 0.f;// Initialize movement component
	if(!MovementComp)
	{
		// Create movement component
	/*	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
		MovementComp->InitialSpeed = InitialSpeed;
		MovementComp->MaxSpeed = MaxSpeed;
		MovementComp->ProjectileGravityScale = GravityScale;
		MovementComp->Bounciness = Bounciness;
		MovementComp->bSimulationEnabled = true;*/
	}

	OnDestroyed.AddDynamic(this, &AEDExplosive::Explode);
}

void AEDExplosive::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Super::HandleHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	Logger::Info(TEXT("Grenade Hit: %s"), *OtherActor->GetName());
}

void AEDExplosive::ApplyDamage(AActor* DamagedActor, const FHitResult& Hit)
{
	// Draw the actual blast radius to the world
	if(Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, BlastRadius / 2, 12, FColor::Red, false, .5, 0, 3.f);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, BlastRadius, 12, FColor::Yellow, false, .5, 0, 3.f);
	}

	float ActualDamage = Damage;
	FVector BlastLocation = GetActorLocation();

	// apply damage to actors in the vicinity excluding the Owner
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


	// check if Owner is in the blast radius, deal reduced damage if so
	if(!NoSelfDamage)
	{
		TArray<FHitResult> OutHits;
		FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(BlastRadius);

		// Calculate the damage
		ActualDamage *= SelfDamageScale;

		// Empty ignored actors list (used before this)
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
}

void AEDExplosive::Explode(AActor* DirectHitActor)
{
	RadialForceComp->FireImpulse();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, DirectHitActor->GetActorLocation(), DirectHitActor->GetActorRotation());

	if(Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), RadialForceComp->GetComponentLocation(), BlastRadius, 12, FColor::White, false, 1.f, 0, 3.f);
	}

	EDOnExplode();
}