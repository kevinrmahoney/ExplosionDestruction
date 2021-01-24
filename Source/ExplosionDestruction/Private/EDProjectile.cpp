// Fill out your copyright notice in the Description page of Project Settings.


#include "EDProjectile.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
}

// Called when the game starts or when spawned
void AEDProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SpriteComp->OnComponentHit.AddDynamic(this, &AEDProjectile::HandleHit);
}

void AEDProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}

// Called every frame
void AEDProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
