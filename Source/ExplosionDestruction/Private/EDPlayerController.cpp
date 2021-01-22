// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPlayerController.h"
#include "ExplosionDestruction.h"
#include "EDCharacter.h"

class AEDCharacter;

void AEDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    bShowMouseCursor = true;

    // When Jump button is pressed or released
    InputComponent->BindAction("Jump", IE_Pressed, this, &AEDPlayerController::JumpPressed);
    InputComponent->BindAction("Jump", IE_Released, this, &AEDPlayerController::JumpReleased);

    // When Shoot button is pressed or released
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AEDPlayerController::ShootPressed);
    InputComponent->BindAction("Shoot", IE_Released, this, &AEDPlayerController::ShootReleased);

    // When Move buttons are pressed or released (TODO: refactor these to be actions)
    InputComponent->BindAxis("MoveRight", this, &AEDPlayerController::Move);
}

void AEDPlayerController::Move(float Movement)
{
    if(AEDCharacter* Char = Cast<AEDCharacter>(GetPawn()))
    {
        Char->SetMoving(Movement);
    }
}

void AEDPlayerController::ShootPressed()
{
    if(AEDCharacter * Char = Cast<AEDCharacter>(GetPawn()))
    {
        Char->SetShooting(true);
    }
}

void AEDPlayerController::ShootReleased()
{
    if(AEDCharacter* Char = Cast<AEDCharacter>(GetPawn()))
    {
        Char->SetShooting(false);
    }
}

void AEDPlayerController::JumpPressed()
{
    if(AEDCharacter* Char = Cast<AEDCharacter>(GetPawn()))
    {
        Char->SetJumping(true);
    }
}

void AEDPlayerController::JumpReleased()
{
    if(AEDCharacter* Char = Cast<AEDCharacter>(GetPawn()))
    {
        Char->SetJumping(false);
    }
}