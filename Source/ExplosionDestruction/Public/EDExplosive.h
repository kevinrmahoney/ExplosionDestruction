// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "EDExplosive.generated.h"


UENUM(BlueprintType)
enum class EMathematicalModel : uint8
{
	Constant,
	Linear,
	Exponential,
	Quadratic
};

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDExplosive : public AEDProjectile
{
	GENERATED_BODY()

public:
	AEDExplosive();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handles when the explosive hits something
	virtual void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	// Applies damage
	virtual void ApplyDamage(AActor* DamagedActor, const FHitResult& Hit) override;

	// Direct hit?
	UFUNCTION()
	virtual void Explode(AActor* DirectHitActor);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* BlastEffect;

	// Make it hidden to blueprint, we edit the values in code, expose some vars to BP that write to this
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URadialForceComponent* RadialForceComp;

	// Explosive damage properties
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float BlastRadius = 300.f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float BlastDamage = 50.f;

	// Unimplemented. Need to rewrite damage logic completely to do this.
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	EMathematicalModel DamageModel = EMathematicalModel::Linear;

	// Knockback properties
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	bool CausesKnockback = true;

	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float KnockbackVelocity = 3000.f;

	// TODO: Unimplemented. Probably need to do knockback manually to do this, so maybe not worth it.
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float MinKnockback = 100.f;

	// TODO: Unimplemented. Probably need to make two radial force components, or do it manually
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	bool NoSelfKnockback = false;

	// TODO: Unimplemented. Probably need to make two radial force components, or do it manually
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	float SelfKnockbackScale = 1.f;

	// Unimplemented. Need to rewrite knockback logic completely to do this.
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	EMathematicalModel KnockbackModel = EMathematicalModel::Linear;

};
