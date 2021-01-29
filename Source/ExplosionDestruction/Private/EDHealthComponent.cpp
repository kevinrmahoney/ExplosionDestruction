// Fill out your copyright notice in the Description page of Project Settings.


#include "EDHealthComponent.h"
#include "Environment.h"

// Sets default values for this component's properties
UEDHealthComponent::UEDHealthComponent()
{
	MaxHealth = 100.f;
}


// Called when the game starts
void UEDHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddDynamic(this, &UEDHealthComponent::HandleTakeAnyDamage);
	}

	Health = MaxHealth;
}

void UEDHealthComponent::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);

	if (Environment::DebugLogs > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Changed: %s"), *FString::SanitizeFloat(Health));
	}

	OnHealthChanged.Broadcast(this, Health, Damage, DamageType, InstigatedBy, DamageCauser);
}

void UEDHealthComponent::Heal(float HealAmount)
{
	if (HealAmount <= 0.f || Health <= 0.f)
	{
		return;
	}

	Health = FMath::Clamp(Health + HealAmount, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(this, Health, -HealAmount, nullptr, nullptr, nullptr);
}
