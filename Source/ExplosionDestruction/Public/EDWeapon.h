// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDWeapon.generated.h"

class UPaperSpriteComponent;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEDWeapon();

protected:
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Cooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Ammo = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage = 20.f;

	float CooldownProgress = Cooldown; // Set progress to Cooldown so we can shoot right away after spawning.

public:

	virtual void Shoot();
};
