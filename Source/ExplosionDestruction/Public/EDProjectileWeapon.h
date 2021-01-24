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
	virtual void Tick(float DeltaSeconds) override;

	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AEDProjectile> ProjectileClass;

	AEDProjectile* FiredProjectile;
};
