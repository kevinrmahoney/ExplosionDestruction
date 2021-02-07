// Fill out your copyright notice in the Description page of Project Settings.


#include "EDWeapon.h"
#include "Logger.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEDWeapon::AEDWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	RootComponent = SpriteComp;
}

void AEDWeapon::Shoot()
{
	// This makes the projectile destroy itself after a time
	IsCoolingDown = true;
	GetWorldTimerManager().SetTimer(CooldownTimer, this, &AEDWeapon::CooldownEnd, Cooldown, true);
}

bool AEDWeapon::CanShoot()
{
	// We should only allow shooting if the gun isnt cooling down, if ammo is there
	// if the gun actually has someone holding it, and if we can get the world.
	return !IsCoolingDown && Ammo > 0.f && GetOwner() && GetWorld();
}

void AEDWeapon::CooldownEnd()
{
	IsCoolingDown = false;
	EDOnCooldownEnd();
}

bool AEDWeapon::PullTrigger()
{
	IsTriggerPulled = true;

	// Only shoot the gun if we can shoot!
	if(CanShoot())
	{
		EDOnShootBegin();
		Shoot();
		return true;
	}

	return false;
}

bool AEDWeapon::ReleaseTrigger()
{
	IsTriggerPulled = false;
	EDOnShootEnd();

	return true;
}

bool AEDWeapon::GetIsTriggerPulled()
{
	return IsTriggerPulled;
}