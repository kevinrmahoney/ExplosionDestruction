// Fill out your copyright notice in the Description page of Project Settings.


#include "EDRocket.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Environment.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"

AEDRocket::AEDRocket()
{
	BlastRadius = 300.f;
	BaseDamage = 50.f;
	BlastStrength = 2000.f;
	ExplosionDelay = 0.f;
	DamageRadius = 200.f;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->Radius = BlastRadius;
	RadialForceComp->ImpulseStrength = BlastStrength;
	RadialForceComp->ForceStrength = 0.f; // we aren't using the force
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Linear;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetupAttachment(SpriteComp);
}

void AEDRocket::BeginPlay()
{
	Super::BeginPlay();

	RadialForceComp->Radius = BlastRadius;
	RadialForceComp->ImpulseStrength = BlastStrength;

	GetWorldTimerManager().SetTimer(TimerHandle_ExplosionDelay, this, &AEDRocket::DestroySelf, ExplosionDelay, true);

	OnDestroyed.AddDynamic(this, &AEDRocket::Explode);
}

void AEDRocket::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDamage(OtherActor, Hit);

	if (bShouldDestroyOnHit)
	{
		Destroy();
		EDOnExplode();
	}
	if(Hit.bBlockingHit)
	{
		EDOnCollide();
	}
}

void AEDRocket::ApplyDamage(AActor* DamagedActor, const FHitResult& Hit)
{

	if (Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, DamageRadius / 2, 12, FColor::Red, false, .5, 0, 3.f);
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, DamageRadius, 12, FColor::Yellow, false, .5, 0, 3.f);
	}

	float ActualDamage = BaseDamage;
	FVector BlastLocation = GetActorLocation();

	// apply damage to actors in the vicinity excluding the Owner
	TArray<AActor*> IgnoredActors;
	IgnoredActors.Add(GetOwner());
	UGameplayStatics::ApplyRadialDamageWithFalloff(
		GetWorld(),
		ActualDamage,
		ActualDamage / 2,
		GetActorLocation(),
		DamageRadius / 2,
		DamageRadius,
		1.f,
		nullptr,
		IgnoredActors,
		this,
		this->GetInstigatorController(),
		COLLISION_WEAPON);

	// check if Owner is in the blast radius, deal reduced damage if so
	TArray<FHitResult> OutHits;
	FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(DamageRadius);
	ActualDamage /= 2;
	IgnoredActors.Empty();
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, BlastLocation, BlastLocation, FQuat::Identity, COLLISION_WEAPON, ExplosionSphere);
	if (isHit)
	{
		for (auto& Result : OutHits)
		{
			AActor* HitActor = Result.GetActor();
			if (HitActor && HitActor != GetOwner())
			{
				IgnoredActors.Add(HitActor);
			}
		}
		UGameplayStatics::ApplyRadialDamageWithFalloff(
			GetWorld(),
			ActualDamage,
			ActualDamage / 2,
			GetActorLocation(),
			DamageRadius / 2,
			DamageRadius,
			1.f,
			nullptr,
			IgnoredActors,
			this,
			this->GetInstigatorController(),
			COLLISION_WEAPON);
	}
}

void AEDRocket::Explode(AActor* DirectHitActor)
{
	RadialForceComp->FireImpulse();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, DirectHitActor->GetActorLocation(), DirectHitActor->GetActorRotation());

	if (Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), RadialForceComp->GetComponentLocation(), BlastRadius, 12, FColor::White, false, 1.f, 0, 3.f);
	}

	EDOnExplode();
}

void AEDRocket::DestroySelf()
{
	Destroy();
}
