// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"
#include "Logger.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "EDProjectile.generated.h"

class UPaperSpriteComponent;
class UProjectileMovementComponent;
class AEDProjectileWeapon;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEDProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	UProjectileMovementComponent* MovementComp;


	// Behavioral properties
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool DestroyOnHit;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool DestroyOnOverlap;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool HitShooter;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool OverlapShooter;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool HitOthers;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool OverlapOthers;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	float LifeSpan;


	// Damage properties
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool SelfDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float SelfDamageScale;

	// End
	FTimerHandle DestroyDelay;

	// Collision events
	UFUNCTION()
	virtual void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Damage handler
	UFUNCTION()
	virtual void ApplyDamage(AActor* DamagedActor, const FHitResult& Hit);

	// Used to self destruct this projectile after an alloted time has passed (useful for things like grenades)
	UFUNCTION()
	virtual void SelfDestruct();

	// Binding: OnDestroy
	UFUNCTION()
	virtual void Destruct(AActor* Actor);

	// Internal function, used where we want the same functionality as Destruct(AActor* Actor)
	// but we don't want to specify the actor (default to self)
	virtual void Destruct();

	// Play events
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Shot"))
	void EDOnShot();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Explode"))
	void EDOnExplode();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Collide"))
	void EDOnCollide();

};
