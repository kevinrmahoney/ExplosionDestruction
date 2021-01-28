// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectileWeapon.h"
#include "PaperSpriteComponent.h"
#include "Logger.h"
#include "EDProjectile.h"

void AEDProjectileWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Play the end cooldown event when its ready to be fired.
	if(CooldownProgress >= Cooldown)
		EDOnCooldownEnd();
}

void AEDProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(!ProjectileClass)
		Logger::Fatal(TEXT("Projectile weapon has no projectile!"));
}

bool AEDProjectileWeapon::Shoot()
{
	// Dont shoot if we're still cooling down
	if(CooldownProgress < Cooldown)
		return false;

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

		// Reset cooldown
		CooldownProgress = 0.f;

		// Return true, because we successfully shot.
		return true;
	}

	return false;
}
