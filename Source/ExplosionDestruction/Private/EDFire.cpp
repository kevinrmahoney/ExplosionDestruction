// Fill out your copyright notice in the Description page of Project Settings.


#include "EDFire.h"
#include "PaperSpriteComponent.h"
#include "Components/BoxComponent.h"
#include "EDFireStarter.h"
#include "Logger.h"
#include "EDCharacter.h"

// Sets default values
AEDFire::AEDFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);

	SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteComp"));
	SpriteComp->CanCharacterStepUpOn = ECB_No;
	SpriteComp->SetCollisionProfileName(TEXT("NoCollision"));
	SetRootComponent(SpriteComp);

	HeatArea = CreateDefaultSubobject<UBoxComponent>(TEXT("HeatArea"));
	HeatArea->CanCharacterStepUpOn = ECB_No;
	HeatArea->SetCollisionProfileName(TEXT("Fire"));
	HeatArea->SetupAttachment(SpriteComp);

	FireArea = CreateDefaultSubobject<UBoxComponent>(TEXT("FireArea"));
	FireArea->CanCharacterStepUpOn = ECB_No;
	HeatArea->SetCollisionProfileName(TEXT("Fire"));
	FireArea->SetupAttachment(SpriteComp);

	EngulfedArea = CreateDefaultSubobject<UBoxComponent>(TEXT("EngulfedArea"));
	EngulfedArea->CanCharacterStepUpOn = ECB_No;
	HeatArea->SetCollisionProfileName(TEXT("Fire"));
	EngulfedArea->SetupAttachment(SpriteComp);

	InstantDeathArea = CreateDefaultSubobject<UBoxComponent>(TEXT("InstantDeathArea"));
	InstantDeathArea->CanCharacterStepUpOn = ECB_No;
	HeatArea->SetCollisionProfileName(TEXT("Fire"));
	InstantDeathArea->SetupAttachment(SpriteComp);

}

// Called when the game starts or when spawned
void AEDFire::BeginPlay()
{
	Super::BeginPlay();

	Started = false;

	Speed = StartingSpeed;

	SpriteComp->SetVisibility(false, true);

	HeatArea->OnComponentBeginOverlap.AddDynamic(this, &AEDFire::OnHeatBeginOverlap);
	HeatArea->OnComponentEndOverlap.AddDynamic(this, &AEDFire::OnHeatEndOverlap);

	FireArea->OnComponentBeginOverlap.AddDynamic(this, &AEDFire::OnFireBeginOverlap);
	FireArea->OnComponentEndOverlap.AddDynamic(this, &AEDFire::OnFireEndOverlap);

	EngulfedArea->OnComponentBeginOverlap.AddDynamic(this, &AEDFire::OnEngulfedBeginOverlap);
	EngulfedArea->OnComponentEndOverlap.AddDynamic(this, &AEDFire::OnEngulfedEndOverlap);

	InstantDeathArea->OnComponentBeginOverlap.AddDynamic(this, &AEDFire::OnInstantDeathBeginOverlap);

	Direction = GetActorRotation().RotateVector(Direction);
}

void AEDFire::Initialize(FVector InitLocation, FRotator InitRotation, float InitFuel, float InitSpeed)
{
	SetActorLocation(InitLocation);
	SetActorRotation(InitRotation);
	Fuel = InitFuel;
	Speed = InitSpeed;
}

// Called every frame
void AEDFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(!Started)
		return;

	FVector CurrentLocation = GetActorLocation();

	Speed = FMath::Clamp(Speed, MinSpeed, MaxSpeed);

	SetActorLocation(CurrentLocation + Direction * (Speed + Fuel) * DeltaTime);

	Fuel = FMath::Max(0.f, --Fuel);

	AActor* DamagedActor;

	// Deal damage
	for(int i = 0; i < OnHeatArray.Num(); i++)
	{
		DamagedActor = OnHeatArray[i];
		DamagedActor->TakeDamage(HeatDamagePerSecond * DeltaTime, FDamageEvent(), nullptr, this);
	}

	// Deal damage
	for(int i = 0; i < OnFireArray.Num(); i++)
	{
		DamagedActor = OnFireArray[i];
		DamagedActor->TakeDamage(FireDamagePerSecond * DeltaTime, FDamageEvent(), nullptr, this);
	}

	// Deal damage
	for(int i = 0; i < OnEngulfedArray.Num(); i++)
	{
		DamagedActor = OnEngulfedArray[i];
		DamagedActor->TakeDamage(EngulfedDamagePerSecond * DeltaTime, FDamageEvent(), nullptr, this);
	}

}

void AEDFire::Start()
{
	Started = true;
	SpriteComp->SetVisibility(true, true);
}

void AEDFire::AddFuel(float AddedFuel)
{
	Fuel += AddedFuel;
	
	Logger::Info(TEXT("Fuel '%f' added to fire '%s'! It is now going speed '%f'!"), AddedFuel, *GetName(), Speed/100.f);
}

void AEDFire::OnHeatBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnHeatArray.Add(OtherActor);
	Logger::Info(TEXT("Character '%s' is in heat!"), *OtherActor->GetName());
}

void AEDFire::OnHeatEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnHeatArray.Remove(OtherActor);
	Logger::Info(TEXT("Character '%s' is no longer in heat!"), *OtherActor->GetName());
}

void AEDFire::OnFireBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnFireArray.Add(OtherActor);
	Logger::Info(TEXT("Character '%s' is on fire!"), *OtherActor->GetName());
}

void AEDFire::OnFireEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnFireArray.Remove(OtherActor);
	Logger::Info(TEXT("Actor '%s' is no longer on fire!"), *OtherActor->GetName());
}

void AEDFire::OnEngulfedBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnEngulfedArray.Add(OtherActor);
	Logger::Info(TEXT("Actor '%s' is engulfed!"), *OtherActor->GetName());
}

void AEDFire::OnEngulfedEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnEngulfedArray.Remove(OtherActor);
	Logger::Info(TEXT("Actor '%s' is no longer engulfed!"), *OtherActor->GetName());
}

void AEDFire::OnInstantDeathBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->TakeDamage(10000.f, FDamageEvent(), nullptr, this);; // Should be enough to kill them!
	Logger::Info(TEXT("OtherActor '%s' is instantly dead!"), *OtherActor->GetName());
}