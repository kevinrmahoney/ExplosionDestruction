// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDHitscanWeapon.h"
#include "EDRailgun.generated.h"

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDRailgun : public AEDHitscanWeapon
{
	GENERATED_BODY()

	AEDRailgun();

	void Shoot() override;
	
};
