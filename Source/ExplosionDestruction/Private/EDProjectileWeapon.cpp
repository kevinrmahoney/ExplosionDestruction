// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectileWeapon.h"
#include "PaperSpriteComponent.h"
#include "Logger.h"
#include "EDProjectile.h"


void AEDProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(!ProjectileClass)
		Logger::Error(TEXT("Projectile weapon has no projectile!"));
}

void AEDProjectileWeapon::Shoot()
{
	Super::Shoot();

	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass && GetWorld())
	{
		/* Shouldnt deproject mouse postion because the mouse position can be between the weapon pivot and the weapon muzzle.
		// Get the mouse location on screen.
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		// Reset the Y plane because its unnecessary in 2d
		MouseWorldLocation.Y = 0.f;

		*/

		// Find the muzzle location on the gun
		FVector MuzzleLocation = Muzzle->GetComponentLocation();
		MuzzleLocation.Y = 0.f;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = MyOwner;

		// Calculate rotation (NOTE: See above note about not using deprojected mouse position
		// FRotator MouseRotation = (MouseWorldLocation - MuzzleLocation).Rotation();

		// Spawn the projectile into the world.
		FiredProjectile = GetWorld()->SpawnActor<AEDProjectile>(ProjectileClass, MuzzleLocation, Muzzle->GetComponentRotation(), SpawnParams);

		// Play events
		EDOnShootBegin();
		EDOnCooldownBegin();
	}
}