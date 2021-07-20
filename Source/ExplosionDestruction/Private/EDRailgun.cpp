// Fill out your copyright notice in the Description page of Project Settings.


#include "EDRailgun.h"
#include "Kismet/GameplayStatics.h"
#include "Logger.h"
#include "EDCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Environment.h"

AEDRailgun::AEDRailgun()
{
	Cooldown = 2.f;
	Ammo = 10.f;
	BaseDamage = 100.f;
	HitImpulse = 10.f;
	Kickback = 15000.f;
	Range = 500.f;
}

void AEDRailgun::Shoot()
{
	AEDWeapon::Shoot();

	// Get the person shooting the weapon and their location
	AActor* Shooter = GetOwner();
	FVector ActorLocation = Shooter->GetActorLocation();
	FVector MouseWorldLocation;
	FVector MouseWorldDirection;
	FVector TraceEnd;
	FVector KickbackVector;
	float Damage = BaseDamage;

	// Get location of the mouse cursor. Make sure to remove the Y component since this is 2D
	ActorLocation.Y = 0.f;
	GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
	MouseWorldLocation.Y = 0.f;
	TraceEnd = (MouseWorldLocation - ActorLocation) * Range + ActorLocation;

	// Ingore the shooter and this weapon
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(Shooter);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	// Find actors in the line to the mouse cursor
	FVector TraceEndPoint = TraceEnd;
	TArray<FHitResult> Hits;

	// Do a multi line trace, potentially hitting multiple objects
	if(GetWorld()->LineTraceMultiByChannel(Hits, ActorLocation, TraceEnd, ECC_Railgun, QueryParams))
	{
		// Go through each hit result
		for(FHitResult Hit : Hits)
		{
			// calculate damage
			AActor* HitActor = Hit.GetActor();
			//UGameplayStatics::ApplyPointDamage(HitActor, BaseDamage, Shooter->GetActorRotation().Vector(), Hit, Shooter->GetInstigatorController(), this, nullptr);

			HitActor->TakeDamage(Damage, FDamageEvent(), nullptr, Shooter);

			Logger::Info(Environment::DebugHits > 0, TEXT("Shooter '%s' hit actor '%s' for %f damage!"), *Shooter->GetName(), *HitActor->GetName(), Damage);
		}
	}
	else
	{
		Logger::Info(Environment::DebugHits > 0, TEXT("Shooter '%s' missed!"), *Shooter->GetName());
	}

	// Find the kickback vectors. its in the opposite direction of where we shot.
	KickbackVector = -1.f * (MouseWorldLocation - ActorLocation).GetSafeNormal() * Kickback;

	// Get static mesh so we can apply an impulse to it
	AEDCharacter* Actor = Cast<AEDCharacter>(Shooter);

	// Apply kickback if we are falling
	if(Actor && Actor->GetCharacterMovement() && Actor->GetCharacterMovement()->IsFalling())
	{
		Actor->GetCharacterMovement()->AddImpulse(KickbackVector, false);
	}

	// Draw a debug line (TODO: Add some actual effects.
	DrawDebugLine(GetWorld(), ActorLocation, TraceEnd, FColor::Green, false, 0.5f, 0, 2.f);
}