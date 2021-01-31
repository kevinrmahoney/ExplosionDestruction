// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectileWeapon.h"
#include "PaperSpriteComponent.h"
#include "Logger.h"
#include "EDProjectile.h"


void AEDProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(!ProjectileClass)
		Logger::Fatal(TEXT("Projectile weapon has no projectile!"));
}

void AEDProjectileWeapon::Shoot()
{
	Super::Shoot();

	AActor* MyOwner = GetOwner();
	if (MyOwner && ProjectileClass && GetWorld())
	{
		// Get the mouse location on screen.
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);

		// Reset the Y plane because its unnecessary in 2d
		MouseWorldLocation.Y = 0.f;

		// Find the muzzle location on the gun
		FVector MuzzleLocation = SpriteComp->GetComponentLocation();
		MuzzleLocation.Y = 0.f;
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Owner = MyOwner;

		// Calculate rotation
		FRotator MouseRotation = (MouseWorldLocation - MuzzleLocation).Rotation();

		// Spawn the projectile into the world.
		FiredProjectile = GetWorld()->SpawnActor<AEDProjectile>(ProjectileClass, MuzzleLocation, MouseRotation, SpawnParams);

		// Play events
		EDOnShootBegin();
		EDOnCooldownBegin();
	}
}