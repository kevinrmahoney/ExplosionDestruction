// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectile.h"
#include "Logger.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEDProjectile::AEDProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create sprite component
	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));

	if(!SpriteComp)
		Logger::Error(TEXT("Failed to create sprite component in projectile!"));
	else
	{
		// Sprites should use a non-default collision profile called Projectile
		SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

		// tells the projectile it should generate hit events
		SpriteComp->BodyInstance.bNotifyRigidBodyCollision = true;
		SetRootComponent(SpriteComp);
	}

	// Create movement component
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));

	if(!MovementComp)
		Logger::Error(TEXT("Failed to create sprite component in projectile!"));

	// NOTE: Child classes should set default values. This should be considered a mostly abstract class with
	// with minimal base functionality to handle damage, hits, and overlaps. Copy+paste the below to new 
	// sublcass projectiles to set the defeault values.

	/* Settings for projectiles. Copy + paste these to new explosive sublcasses

	// Projectile properties
	DestroyOnHit = false;
	DestroyOnOverlap = false;
	HitShooter = false;
	OverlapShooter = false;
	HitOthers = false;
	OverlapOthers = false;
	LifeSpan = 10.f;

	Damage = 20.f;
	SelfDamage = false;
	SelfDamageScale = 1.f;

	MovementComp->InitialSpeed = 1000.f;
	MovementComp->MaxSpeed = 1000.f;
	MovementComp->bSimulationEnabled = true;
	MovementComp->bShouldBounce = false;
	MovementComp->Bounciness = 0.f;
	MovementComp->ProjectileGravityScale = 0.f;
	*/

}

// Called when the game starts or when spawned
void AEDProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComp->OnComponentHit.AddDynamic(this, &AEDProjectile::HandleHit);
	SpriteComp->OnComponentBeginOverlap.AddDynamic(this, &AEDProjectile::HandleOverlap);

	// This makes the projectile destroy itself after a time
	GetWorldTimerManager().SetTimer(DestroyDelay, this, &AEDProjectile::SelfDestruct, LifeSpan, true);

	// This binds the OnDestroyed event to 
	OnDestroyed.AddDynamic(this, &AEDProjectile::Destruct);

	EDOnShot();
}

void AEDProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// This is called on a direct hit
void AEDProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	bool HitActorIsShooter = MyOwner && (MyOwner == OtherActor);

	// Apply damage to enemies on hit
	if (!HitActorIsShooter && HitOthers)
	{
		ApplyDamage(OtherActor, Hit);

		if (DestroyOnHit)
			Destruct();
	}
	// Applies damage to self on hit
	else if(HitActorIsShooter && HitShooter)
	{
		ApplyDamage(OtherActor, Hit);

		if(DestroyOnHit)
			Destruct();
	}
	// If we hit something else, simply collide with it.
	else if(Hit.bBlockingHit)
	{
		EDOnCollide();
	}
}

void AEDProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* Shooter = GetOwner();
	bool OverlappedActorIsShooter = Shooter && Shooter == OtherActor;

	// Apply damage to enemies on overlap
	if(!OverlappedActorIsShooter && HitOthers)
	{
		ApplyDamage(OtherActor, SweepResult);

		if(DestroyOnOverlap)
		{
			Destruct();
		}
	}
	// Applies damage to self on overlap
	else if(OverlappedActorIsShooter && HitShooter)
	{
		ApplyDamage(OtherActor, SweepResult);

		if(DestroyOnHit)
		{
			Destruct();
		}
	}
}

// Apply damage to thing hit. Scale it based on if its the owner or not.
// If we have self damage disabled, then return early.
void AEDProjectile::ApplyDamage(AActor* DamagedActor, const FHitResult& Hit)
{
	float ActualDamage = Damage;

	// Check if the damaged actor is the shooter
	if(DamagedActor == GetOwner())
	{
		// If no self damage, return early
		if(!SelfDamage)
			return;
		else // Otherwise, calculate the damage
			ActualDamage *= SelfDamageScale;
	}

	UGameplayStatics::ApplyPointDamage(DamagedActor, ActualDamage, Hit.ImpactNormal, Hit, GetInstigatorController(), this, nullptr);
}

// We specify an actor because in order to bind this event to OnDestroy, we need to have 
// the actor as an argument. Yes, makes little sense, but alas.
void AEDProjectile::Destruct(AActor* DestroyedActor)
{
	EDOnExplode();

	if(DestroyedActor)
		DestroyedActor->Destroy();
}

void AEDProjectile::Destruct()
{
	Destruct(this);
}

// Unless we are specifying it as an ondestroy event, just use this version of DestroySelf()
void AEDProjectile::SelfDestruct()
{
	Destroy();
}