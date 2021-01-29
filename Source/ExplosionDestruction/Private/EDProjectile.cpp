// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectile.h"
#include "Logger.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEDProjectile::AEDProjectile()
{

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// Initialize movement component
	if(!MovementComp)
	{
		// Create movement component
		MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
		MovementComp->InitialSpeed = InitialSpeed;
		MovementComp->MaxSpeed = MaxSpeed;
		MovementComp->ProjectileGravityScale = GravityScale;
		MovementComp->Bounciness = Bounciness;
		MovementComp->bSimulationEnabled = true;
	}

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// tells the projectile it should generate hit events
	SpriteComp->BodyInstance.bNotifyRigidBodyCollision = true;

	RootComponent = SpriteComp;
}

// Called when the game starts or when spawned
void AEDProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComp->OnComponentHit.AddDynamic(this, &AEDProjectile::HandleHit);
	SpriteComp->OnComponentBeginOverlap.AddDynamic(this, &AEDProjectile::HandleOverlap);

	// This makes the projectile destroy itself after a time
	GetWorldTimerManager().SetTimer(DestroyDelay, this, &AEDProjectile::DestroySelf, LifeSpan, true);

	EDOnShot();
}

void AEDProjectile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AEDProjectile::Tick(float DeltaTime)
{
	static int counter = 0;
	Super::Tick(DeltaTime);
	if(counter == 0)
	{
		Logger::Info(TEXT("Speed: %f"), GetVelocity().Size());
		Logger::Info(TEXT("Component Speed: %f"), MovementComp->InitialSpeed);
	}
	counter++;
}

// This is called on a direct hit
void AEDProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	bool IfHitActorIsOwner = MyOwner && MyOwner == OtherActor;

	// Apply damage to enemies on hit
	if (!IfHitActorIsOwner && !IgnoresOthersOnHit)
	{
		ApplyDamage(OtherActor, Hit);

		if (ShouldDestroyOnHit)
			DestroySelf();
	}
	// Applies damage to self on hit
	else if(IfHitActorIsOwner && !IgnoresSpawnerOnHit)
	{
		ApplyDamage(OtherActor, Hit);

		if(ShouldDestroyOnHit)
			DestroySelf();
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
	AActor* MyOwner = GetOwner();
	bool IfOverlappedActorIsOwner = MyOwner && MyOwner == OtherActor;

	// Apply damage to enemies on overlap
	if(!IfOverlappedActorIsOwner && !IgnoresOthersOnOverlap)
	{
		ApplyDamage(OtherActor, SweepResult);

		if(ShouldDestroyOnOverlap)
		{
			DestroySelf();
		}
	}
	// Applies damage to self on overlap
	else if(IfOverlappedActorIsOwner && !IgnoresSpawnerOnOverlap)
	{
		PRINTFUNC
		ApplyDamage(OtherActor, SweepResult);

		if(ShouldDestroyOnHit)
		{
			DestroySelf();
		}
	}
}

// Apply damage to thing hit. Scale it based on if its the owner or not.
// If we have self damage disabled, then return early.
void AEDProjectile::ApplyDamage(AActor* DamagedActor, const FHitResult& Hit)
{
	float ActualDamage = Damage;

	if(DamagedActor == GetOwner())
	{
		if(NoSelfDamage)
			return;
		else
			ActualDamage *= SelfDamageScale;
	}

	UGameplayStatics::ApplyPointDamage(DamagedActor, ActualDamage, Hit.ImpactNormal, Hit, GetInstigatorController(), this, nullptr);
}

void AEDProjectile::DestroySelf()
{
	Destroy();
	EDOnExplode();
}