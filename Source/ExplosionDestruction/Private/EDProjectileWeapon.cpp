// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectileWeapon.h"
#include "PaperSpriteComponent.h"

void AEDProjectileWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AEDProjectileWeapon::Fire()
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

		// calculate rotation
		FRotator MouseRotation = (MouseWorldLocation - MuzzleLocation).Rotation();
		//FRotator MouseRotation = FRotator(100.01f, 0.f, 100.f);

		GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MouseRotation, SpawnParams);
		UE_LOG(LogTemp, Warning, TEXT("World Rotation: %s"), *MouseRotation.ToString());
	}

	UE_LOG(LogTemp, Warning, TEXT("Cooldown Progress: %f"), CooldownProgress);

	CooldownProgress = 0.f;
}
