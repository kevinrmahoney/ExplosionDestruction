// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDWeapon.h"
#include "EDHitscanWeapon.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDHitscanWeapon : public AEDWeapon
{
	GENERATED_BODY()

protected:

	virtual void Shoot() override;

	// Not to be confused with recoil. How much backwards force is applied when shot
	UPROPERTY(EditDefaultsOnly)
	float Kickback;

	// How much impulse is applied to objects hit with this gun.
	UPROPERTY(EditDefaultsOnly)
	float HitImpulse;

	UPROPERTY(EditDefaultsOnly)
	float Range;
	
};
