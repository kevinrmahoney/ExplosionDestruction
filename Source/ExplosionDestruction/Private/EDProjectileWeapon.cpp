// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectileWeapon.h"
#include "PaperSpriteComponent.h"
#include "EDProjectile.h"

void AEDProjectileWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEDProjectileWeapon::Shoot()
{
	// Dont shoot if we're still cooling down
	if(CooldownProgress < Cooldown)
		return;

	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass)
	{
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		MouseWorldLocation.Y = 0.f;

		FVector MuzzleLocation = SpriteComp->GetComponentLocation();
		MuzzleLocation.Y = 0.f;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = MyOwner;

		// calculate rotation
		FRotator MouseRotation = (MouseWorldLocation - MuzzleLocation).Rotation();

		GetWorld()->SpawnActor<AEDProjectile>(ProjectileClass, MuzzleLocation, MouseRotation, SpawnParams);
	}

	CooldownProgress = 0.f;
}
