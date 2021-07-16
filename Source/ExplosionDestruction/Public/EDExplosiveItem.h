// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EDExplosiveItem.generated.h"

class URadialForceComponent;
class UPaperSpriteComponent;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDExplosiveItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDExplosiveItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.f;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Explode"))
	void EDOnExplode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSpriteComponent * SpriteComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Fuel = 50.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Applies damage
	virtual void ApplyExplosiveDamage();

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

	// What happens as part of the explosion
	virtual void Explode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* BlastEffect;

	// Make it hidden to blueprint, we edit the values in code, expose some vars to BP that write to this
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	URadialForceComponent* RadialForceComp;

	// Explosive damage properties
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float BlastRadius;

	// Knockback properties
	UPROPERTY(EditDefaultsOnly, Category = "Knockback")
	bool CausesKnockback;

	FTimerHandle ExplosionDelay;
};
