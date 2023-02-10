// Fill out your copyright notice in the Description page of Project Settings.


#include "EDCheckpoint.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "Logger.h"
#include "EDPlayerStart.h"
#include "EDGameMode.h"

// Sets default values
AEDCheckpoint::AEDCheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));

	// Create sprite component
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));

	SetRootComponent(BoxComponent);
	Sprite->SetupAttachment(BoxComponent);

	DoorIsOpening = false;
	DoorClosed = true;
	HasTouched = false;
	CanRespawnAt = false;
}

// Called when the game starts or when spawned
void AEDCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	// Set the animation
	if(Sprite->GetFlipbook() != DoorClosedAnimation)
	{
		Sprite->SetFlipbook(DoorClosedAnimation);
	}
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCheckpoint::OnCheckpointBeginOverlap);

	if(GetWorld())
		GameMode = Cast<AEDGameMode>(GetWorld()->GetAuthGameMode());
}

void AEDCheckpoint::OnCheckpointBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Dont bother opening door that already is open.
	if(!DoorClosed)
		return;

	// Set the animation
	if(Sprite->GetFlipbook() != DoorOpeningAnimation)
	{
		Sprite->SetFlipbook(DoorOpeningAnimation);
		GetWorldTimerManager().SetTimer(DoorOpeningTimer, this, &AEDCheckpoint::OnOpeningAnimationDone, Sprite->GetFlipbookLength() - 0.1f, false);
		DoorIsOpening = true;
	}

	HasTouched = true;

	if(RespawnPoint)
	{
		RespawnPoint->Activate();
		CanRespawnAt = true;
	}

	if(GameMode)
		GameMode->CheckpointReached(this);

	EDOnOpenBegin();
}

void AEDCheckpoint::OnOpeningAnimationDone()
{
	// Don't allow us to change animation to open door if we've reset
	if(!DoorIsOpening)
		return;

	DoorClosed = false;
	DoorIsOpening = false;

	// Set the animation
	if(Sprite->GetFlipbook() != DoorOpenAnimation)
	{
		Sprite->SetFlipbook(DoorOpenAnimation);
	}

	EDOnOpenEnd();
}

int AEDCheckpoint::GetCheckpointNumber() const
{
	return CheckpointNumber;
}

AEDPlayerStart* AEDCheckpoint::GetRespawnPoint()
{
	if(RespawnPoint)
		return RespawnPoint;
	else
		return nullptr;
}

// Rest a checkpoint to its default state
void AEDCheckpoint::Reset()
{
	DoorClosed = true;
	DoorIsOpening = false;
	HasTouched = false;
	CanRespawnAt = false;

	// Associated respawn point is deactivated
	if(RespawnPoint)
		RespawnPoint->Deactivate();

	// Set the animation
	if(Sprite->GetFlipbook() != DoorClosedAnimation)
		Sprite->SetFlipbook(DoorClosedAnimation);
}

bool AEDCheckpoint::HasBeenReached()
{
	return HasTouched;
}

void AEDCheckpoint::SetHasBeenReached(bool NewHasBeenReached)
{
	HasTouched = NewHasBeenReached;

	if(HasTouched)
	{
		if(RespawnPoint)
		{
			RespawnPoint->Activate();
			CanRespawnAt = true;
		}
	}
	else
	{
		CanRespawnAt = false;

		if(RespawnPoint)
			RespawnPoint->Deactivate();
	}
}
