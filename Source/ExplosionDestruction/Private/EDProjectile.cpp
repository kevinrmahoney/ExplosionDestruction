// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectile.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEDProjectile::AEDProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	// tells the projectile it should generate hit events
	SpriteComp->BodyInstance.bNotifyRigidBodyCollision = true;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = InitialSpeed;
	MovementComp->MaxSpeed = MaxSpeed;
	MovementComp->ProjectileGravityScale = 0.f;

	RootComponent = SpriteComp;

	bShouldDestroyOnHit = true;
	bShouldDestroyOnOverlap = true;
}

// Called when the game starts or when spawned
void AEDProjectile::BeginPlay()
{
	Super::BeginPlay();

	SpriteComp->OnComponentHit.AddDynamic(this, &AEDProjectile::HandleHit);
	SpriteComp->OnComponentBeginOverlap.AddDynamic(this, &AEDProjectile::HandleOverlap);

	EDOnShot();
}

void AEDProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner != OtherActor)
	{
		ApplyDamage(OtherActor, Hit);

		if (bShouldDestroyOnHit)
		{
			Destroy();
			EDOnExplode();
		}
	}
	else if(Hit.bBlockingHit)
	{
		EDOnCollide();
	}
}

void AEDProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && MyOwner != OtherActor)
	{
		ApplyDamage(OtherActor, SweepResult);

		if (bShouldDestroyOnOverlap)
		{
			Destroy();
		}
	}
}

void AEDProjectile::ApplyDamage(AActor* DamagedActor, const FHitResult& Hit)
{
	UGameplayStatics::ApplyPointDamage(DamagedActor, BaseDamage, Hit.ImpactNormal, Hit, GetInstigatorController(), this, nullptr);
}

// Called every frame
void AEDProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}