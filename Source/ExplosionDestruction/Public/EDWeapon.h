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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* PivotPoint;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* LeftHandGrip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* RightHandGrip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Muzzle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Cooldown = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float Ammo = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float BaseDamage = 20.f;

	bool IsCoolingDown = false;

	bool IsTriggerPulled = false;

	// A timer for handling cooldowns of consecutive shots
	FTimerHandle CooldownTimer;

	virtual void BeginPlay() override;

	// What happens when this gun is shot, and if it can shoot to begin with
	virtual void Shoot();

	// returns if we can actually shoot, given current state of gun
	virtual bool CanShoot();

	// Marks the end of the cooldown
	virtual void CooldownEnd();

	//
	// Events
	//

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Shoot Begin"))
	void EDOnShootBegin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Shoot End"))
	void EDOnShootEnd();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Cooldown Begin"))
	void EDOnCooldownBegin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Cooldown End"))
	void EDOnCooldownEnd();

public:

	// Control if trigger is pulled or not.
	virtual bool PullTrigger();
	virtual bool ReleaseTrigger();

	// Get if the trigger is pulled
	virtual bool GetIsTriggerPulled();

	// The locations of where the grips of either hand is, in world space
	UFUNCTION(BlueprintCallable)
	FVector GetRightHandGripLocation();

	UFUNCTION(BlueprintCallable)
	FVector GetLeftHandGripLocation();
};
