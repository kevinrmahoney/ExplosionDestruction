// Fill out your copyright notice in the Description page of Project Settings.


#include "EDRocket.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Environment.h"
#include "TimerManager.h"

AEDRocket::AEDRocket()
{
	BlastRadius = 150.f;
	BlastStrength = 2000.f;
	ExplosionDelay = 1.f;
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComp"));
	RadialForceComp->Radius = BlastRadius;
	RadialForceComp->ForceStrength = 0.f; // we aren't using the force
	RadialForceComp->Falloff = ERadialImpulseFalloff::RIF_Constant;
	RadialForceComp->ImpulseStrength = BlastStrength;
	RadialForceComp->bImpulseVelChange = true;
	RadialForceComp->SetupAttachment(SpriteComp);
}

void AEDRocket::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle_ExplosionDelay, this, &AEDRocket::DestroySelf, ExplosionDelay, true);

	OnDestroyed.AddDynamic(this, &AEDRocket::Explode);
}

void AEDRocket::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	// later, add custom handling for damage since it will deal radial damage
	Super::HandleHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);
}

void AEDRocket::Explode(AActor* DirectHitActor)
{
	RadialForceComp->FireImpulse();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, DirectHitActor->GetActorLocation(), DirectHitActor->GetActorRotation());

	if (Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), RadialForceComp->GetComponentLocation(), BlastRadius, 12, FColor::White, false, 1.f, 0, 3.f);
	}
}

void AEDRocket::DestroySelf()
{
	Destroy();
}

