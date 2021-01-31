// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDWeapon.h"
#include "EDProjectileWeapon.generated.h"

class AEDProjectile;

/**
 *
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDProjectileWeapon : public AEDWeapon
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	// Shoot the weapon
	virtual void Shoot() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AEDProjectile> ProjectileClass;

	// Save the projectile it fired (TODO: make this into an array?)
	AEDProjectile* FiredProjectile;
};
