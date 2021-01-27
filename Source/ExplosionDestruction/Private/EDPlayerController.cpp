// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPlayerController.h"
#include "ExplosionDestruction.h"
#include "EDCharacter.h"
#include "Logger.h"
#include "EDGameMode.h"

void AEDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if(!InputComponent)
        return;

    bShowMouseCursor = true;

    // When Jump button is pressed or released
    InputComponent->BindAction("Jump", IE_Pressed, this, &AEDPlayerController::JumpPressed);
    InputComponent->BindAction("Jump", IE_Released, this, &AEDPlayerController::JumpReleased);

    // When Shoot button is pressed or released
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AEDPlayerController::ShootPressed);
    InputComponent->BindAction("Shoot", IE_Released, this, &AEDPlayerController::ShootReleased);

    // When Move buttons are pressed or released (TODO: refactor these to be actions)
    InputComponent->BindAxis("MoveRight", this, &AEDPlayerController::Move);

    // Kill the current character (if it is a character) if it exists, and respawn
    InputComponent->BindAction("Respawn", IE_Pressed, this, &AEDPlayerController::RespawnPressed);
}

void AEDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    EDGameMode = Cast<AEDGameMode>(GetWorld()->GetAuthGameMode());
}

void AEDPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AEDPlayerController::OnPossess(APawn* NewPawn)
{
    Super::OnPossess(NewPawn);
    AEDCharacter* NewCharacter = Cast<AEDCharacter>(NewPawn);

    if(NewCharacter)
    {
        EDCharacter = NewCharacter;
        PossessedIsEDCharacter = true;
    }
    else
    {
        PossessedIsEDCharacter = false;
    }
}

void AEDPlayerController::OnUnPossess()
{
    Super::OnUnPossess();

    PossessedIsEDCharacter = false;
    EDCharacter = nullptr;
}

void AEDPlayerController::Move(float Movement)
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetMoving(Movement);
}

void AEDPlayerController::ShootPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetShooting(true);
}

void AEDPlayerController::ShootReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetShooting(false);
}

void AEDPlayerController::JumpPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetJumping(true);
}

void AEDPlayerController::JumpReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetJumping(false);
}

// If we pressed the respawn button
void AEDPlayerController::RespawnPressed()
{
    // If currently possessing EDCharacter, kill it first.
    if(PossessedIsEDCharacter && EDGameMode)
    {
        EDGameMode->KillPlayerCharacter(this);
    }

    // Spawn a new character.
    if(GetWorld() && EDGameMode)
    {
        EDGameMode->SpawnCharacter(this);
    }
}