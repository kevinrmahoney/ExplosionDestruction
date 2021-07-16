// Fill out your copyright notice in the Description page of Project Settings.


#include "EDPlayerController.h"
#include "Logger.h"
#include "ExplosionDestruction.h"
#include "EDCharacter.h"
#include "Logger.h"
#include "EDGameMode.h"

void AEDPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if(!InputComponent)
        return;

    GetWorld()->GetGameViewport()->SetMouseLockMode(EMouseLockMode::LockAlways);
    GetWorld()->GetGameViewport()->Viewport->LockMouseToViewport(true);

    bShowMouseCursor = true;

    // When Jump button is pressed or released
    InputComponent->BindAction("Jump", IE_Pressed, this, &AEDPlayerController::JumpPressed);
    InputComponent->BindAction("Jump", IE_Released, this, &AEDPlayerController::JumpReleased);

    // When Shoot button is pressed or released
    InputComponent->BindAction("Shoot", IE_Pressed, this, &AEDPlayerController::ShootPressed);
    InputComponent->BindAction("Shoot", IE_Released, this, &AEDPlayerController::ShootReleased);

    // When move left is pressed
    InputComponent->BindAction("MoveRight", IE_Pressed, this, &AEDPlayerController::MoveRightPressed);
    InputComponent->BindAction("MoveRight", IE_Released, this, &AEDPlayerController::MoveRightReleased);

    // When move right is pressed
    InputComponent->BindAction("MoveLeft", IE_Pressed,  this, &AEDPlayerController::MoveLeftPressed);
    InputComponent->BindAction("MoveLeft", IE_Released, this, &AEDPlayerController::MoveLeftReleased);

    // Begin and end slide
    InputComponent->BindAction("Slide", IE_Pressed, this, &AEDPlayerController::SlidePressed);
    InputComponent->BindAction("Slide", IE_Released, this, &AEDPlayerController::SlideReleased);

    // Switch to the rocket launcher
    InputComponent->BindAction("RocketLauncher", IE_Pressed, this, &AEDPlayerController::RocketLauncherPressed);

    // Switch to the grenade launcher
    InputComponent->BindAction("GrenadeLauncher", IE_Pressed, this, &AEDPlayerController::GrenadeLauncherPressed);

    // Switch to the Assault Rifle
    InputComponent->BindAction("AssaultRifle", IE_Pressed, this, &AEDPlayerController::AssaultRiflePressed);

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


void AEDPlayerController::MoveRightPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->MoveRightBegin();
}

void AEDPlayerController::MoveRightReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->MoveRightEnd();
}

void AEDPlayerController::MoveLeftPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->MoveLeftBegin();
}

void AEDPlayerController::MoveLeftReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->MoveLeftEnd();
}


void AEDPlayerController::ShootPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetShootBegin();
}

void AEDPlayerController::ShootReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetShootEnd();
}

void AEDPlayerController::JumpPressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetJumpBegin();
}

void AEDPlayerController::JumpReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetJumpEnd();
}

void AEDPlayerController::SlidePressed()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetSlideBegin();
}

void AEDPlayerController::SlideReleased()
{
    if(PossessedIsEDCharacter && EDCharacter)
        EDCharacter->SetSlideEnd();
}

void AEDPlayerController::RocketLauncherPressed()
{
    if(PossessedIsEDCharacter && EDCharacter && EDCharacter->bHasRocketLauncher)
        EDCharacter->EquipRocketLauncher();
}

void AEDPlayerController::GrenadeLauncherPressed()
{
    if(PossessedIsEDCharacter && EDCharacter && EDCharacter->bHasGrenadeLauncher)
        EDCharacter->EquipGrenadeLauncher();
}

void AEDPlayerController::AssaultRiflePressed()
{
    if(PossessedIsEDCharacter && EDCharacter && EDCharacter->bHasAssaultRifle)
        EDCharacter->EquipAssaultRifle();
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