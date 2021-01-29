// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float InitialSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float MaxSpeed = 2000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float BaseDamage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	bool bShouldDestroyOnHit;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	bool bShouldDestroyOnOverlap;

	UFUNCTION()
	virtual void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void ApplyDamage(AActor* DamagedActor, const FHitResult& Hit);

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
