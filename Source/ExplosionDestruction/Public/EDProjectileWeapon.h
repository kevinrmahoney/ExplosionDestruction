// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDWeapon.h"
#include "EDProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDProjectileWeapon : public AEDWeapon
{
	GENERATED_BODY()
	
protected:

	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> ProjectileClass;
};
