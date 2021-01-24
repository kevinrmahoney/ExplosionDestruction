// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDProjectile.h"
#include "EDRocket.generated.h"

class URadialForceComponent;
class UParticleSystem;

/**
 * 
 */
UCLASS()
class EXPLOSIONDESTRUCTION_API AEDRocket : public AEDProjectile
{
	GENERATED_BODY()

public:
	AEDRocket();
	
protected:

	void BeginPlay() override;

	void HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

	UFUNCTION()
	void Explode(AActor* DirectHitActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	URadialForceComponent* RadialForceComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float BlastRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float BlastStrength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* BlastEffect;
};
