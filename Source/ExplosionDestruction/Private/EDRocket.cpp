// Fill out your copyright notice in the Description page of Project Settings.


#include "EDRocket.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Environment.h"
#include "Logger.h"

AEDRocket::AEDRocket()
{
	BlastRadius = 100.f;
	BlastStrength = 2000.f;
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
	
	OnDestroyed.AddDynamic(this, &AEDRocket::Explode);
}

void AEDRocket::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                          FVector NormalImpulse, const FHitResult& Hit)
{
	// later, add custom handling for damage since it will deal radial damage
	Super::HandleHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BlastEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

void AEDRocket::Explode(AActor* DirectHitActor)
{
	RadialForceComp->FireImpulse();

	Logger::Info(TEXT("%f"), BlastRadius);

	if (Environment::DebugWeapons > 0)
	{
		DrawDebugSphere(GetWorld(), RadialForceComp->GetComponentLocation(), BlastRadius, 12, FColor::White, false, 1.f, 0, 3.f);
	}
}
