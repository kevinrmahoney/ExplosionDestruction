// Fill out your copyright notice in the Description page of Project Settings.


#include "EDWeapon.h"
#include "Logger.h"
#include "PaperSpriteComponent.h"

// Sets default values
AEDWeapon::AEDWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

	PivotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot Point"));
	SetRootComponent(PivotPoint);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("NoCollision"));
	SpriteComp->SetupAttachment(PivotPoint);

	LeftHandGrip = CreateDefaultSubobject<USceneComponent>(TEXT("Left Hand Grip"));
	LeftHandGrip->SetupAttachment(SpriteComp);

	RightHandGrip = CreateDefaultSubobject<USceneComponent>(TEXT("Right Hand Grip"));
	RightHandGrip->SetupAttachment(SpriteComp);

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(SpriteComp);
}

void AEDWeapon::BeginPlay()
{
	Super::BeginPlay();
	SpriteComp->SetSpriteColor(FLinearColor(1.f, 1.f, 1.f, Environment::DebugWeaponAlpha));
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

FVector AEDWeapon::GetMuzzleLocation()
{
	return Muzzle->GetComponentLocation();
}

FVector AEDWeapon::GetRightHandGripLocation()
{
	return RightHandGrip->GetComponentLocation();
}

FVector AEDWeapon::GetLeftHandGripLocation()
{
	return LeftHandGrip->GetComponentLocation();
}