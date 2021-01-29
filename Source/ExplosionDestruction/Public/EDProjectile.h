// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"
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


	// Movement properties
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float InitialSpeed = 2000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float MaxSpeed = 2000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float Bounciness = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float GravityScale = 1.f;


	// Behavioral properties
	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool ShouldDestroyOnHit = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool ShouldDestroyOnOverlap = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool IgnoresSpawnerOnHit = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool IgnoresSpawnerOnOverlap = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool IgnoresOthersOnHit = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	bool IgnoresOthersOnOverlap = false;

	UPROPERTY(EditDefaultsOnly, Category = "Behavior")
	float LifeSpan = 10.f;


	// Damage properties
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	bool NoSelfDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float SelfDamageScale = 1.f;

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

	virtual void DestroySelf();

	// Play events
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Shot"))
	void EDOnShot();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Explode"))
	void EDOnExplode();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Collide"))
	void EDOnCollide();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
