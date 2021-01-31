// Fill out your copyright notice in the Description page of Project Settings.


#include "EDCheckpoint.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "Logger.h"
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
	Logger::Info(TEXT("OVERLAPPING WITH CHECKPOINT"));

	if(HasTouched)
		return;

	// Set the animation
	if(Sprite->GetFlipbook() != DoorOpeningAnimation)
	{
		Sprite->SetFlipbook(DoorOpeningAnimation);
		GetWorldTimerManager().SetTimer(DoorOpeningTimer, this, &AEDCheckpoint::OnOpeningAnimationDone, Sprite->GetFlipbookLength() - 0.1f, true);
	}

	HasTouched = true;
	CanRespawnAt = true;

	EDOnOpenBegin();
}

void AEDCheckpoint::OnOpeningAnimationDone()
{
	// Set the animation
	if(Sprite->GetFlipbook() != DoorOpenAnimation)
	{
		Sprite->SetFlipbook(DoorOpenAnimation);
	}

	EDOnOpenEnd();
}

int AEDCheckpoint::GetCheckpointNumber()
{
	return CheckpointNumber;
}

FORCEINLINE bool operator <(AEDCheckpoint& ThisCheckpoint, AEDCheckpoint& OtherCheckpoint)
{
	return ThisCheckpoint.GetCheckpointNumber() < OtherCheckpoint.GetCheckpointNumber();
}