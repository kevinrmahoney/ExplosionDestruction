// Copyright Epic Games, Inc. All Rights Reserved.

#include "EDCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "EDWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//////////////////////////////////////////////////////////////////////////
// EDCharacter

AEDCharacter::AEDCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Hit boxes for the wallkicks
	WallKickTopComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickTopComponent"));
	WallKickTopComponent->SetupAttachment(GetSprite());

	WallKickBottomComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickBottomComponent"));
	WallKickBottomComponent->SetupAttachment(GetSprite());

	WallKickLeftComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickLeftComponent"));
	WallKickLeftComponent->SetupAttachment(GetSprite());

	WallKickRightComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickRightComponent"));
	WallKickRightComponent->SetupAttachment(GetSprite());

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	

	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
	SideViewCameraComponent->OrthoWidth = 2048.0f;
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Prevent all automatic rotation behavior on the camera, character, and camera component
	CameraBoom->SetUsingAbsoluteRotation(true);
	SideViewCameraComponent->bUsePawnControlRotation = false;
	SideViewCameraComponent->bAutoActivate = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 1.8f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->GroundFriction = 4.0f;
	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(44.f);
	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.25f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

    // 	TextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("IncarGear"));
    // 	TextComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
    // 	TextComponent->SetRelativeLocation(FVector(35.0f, 5.0f, 20.0f));
    // 	TextComponent->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
    // 	TextComponent->SetupAttachment(RootComponent);

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;

	WeaponSocketName = "WeaponSocket";
}

//////////////////////////////////////////////////////////////////////////
// Animation

void AEDCharacter::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	// Are we moving or standing still?
	UPaperFlipbook* DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	if( GetSprite()->GetFlipbook() != DesiredAnimation 	)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void AEDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateCharacter();

	// Set if the character is on the grounded
	Grounded = !GetCharacterMovement()->IsFalling();

	// Reset JumpCount if we are on the ground
	if(Grounded)
		JumpCount = 0;
	// If we aren't on the ground and we haven't jumped yet, too bad, only get one jump in midair
	else if(JumpCount == 0)
		JumpCount = 1;

	// Fire weapon if we are firing
	if(Shooting && CurrentWeapon)
	{
		CurrentWeapon->Shoot();
	}

	// We can jump if we are on the ground and trying to jump,
	// or if we are in the air and trying to jump so long as we have a
	if((JumpCount < MaxJumpCount) && Jumping)
	{
		GetCharacterMovement()->DoJump(false);
		JumpCount++;
	}

	// Reset states
	Jumping = false;
	
	if(GetCharacterMovement()->Velocity.Size() > 900.f)
		UE_LOG(LogTemp, Warning, TEXT("Velocity: %s (%f)"), *GetCharacterMovement()->Velocity.ToString(), GetCharacterMovement()->Velocity.Size());
}

void AEDCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentWeapon = GetWorld()->SpawnActor<AEDWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if (CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	// Add event for each of the wallkick box components. Need to be in BeginPlay for some reason?
	WallKickTopComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickTopComponentBeginOverlap);
	WallKickTopComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickTopComponentEndOverlap);
	WallKickBottomComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickBottomComponentBeginOverlap);
	WallKickBottomComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickBottomComponentEndOverlap);
	WallKickLeftComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickLeftComponentBeginOverlap);
	WallKickLeftComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickLeftComponentEndOverlap);
	WallKickRightComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickRightComponentBeginOverlap);
	WallKickRightComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickRightComponentEndOverlap);
}

void AEDCharacter::UpdateCharacter()
{
	// Update animation to match the motion
	UpdateAnimation();

	// Now setup the rotation of the controller based on the direction we are travelling
	const FVector PlayerVelocity = GetVelocity();	
	float TravelDirection = MovementInput;
	// Set the rotation so that the character faces his direction of travel.
	if (Controller != nullptr)
	{
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
}

// Called by Controller

void AEDCharacter::SetMoving(float Value)
{
	/*UpdateChar();*/

	MovementInput = Value;

	// Apply the input to the character motion
	AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
}

void AEDCharacter::SetShooting(bool NewShooting)
{
	Shooting = NewShooting;
}

void AEDCharacter::SetJumping(bool NewJumping)
{
	Jumping = NewJumping;
}

// Top
void AEDCharacter::OnWallKickTopComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickTopComponentBeginOverlap"));
}

void AEDCharacter::OnWallKickTopComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickTopComponentEndOverlap"));
}

// Bottom
void AEDCharacter::OnWallKickBottomComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickBottomComponentBeginOverlap"));
}

void AEDCharacter::OnWallKickBottomComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickBottomComponentEndOverlap"));
}

// Left
void AEDCharacter::OnWallKickLeftComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickLeftComponentBeginOverlap"));
}

void AEDCharacter::OnWallKickLeftComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickLeftComponentEndOverlap"));
}

// Right
void AEDCharacter::OnWallKickRightComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickRightComponentBeginOverlap"));
}

void AEDCharacter::OnWallKickRightComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnWallKickRightComponentEndOverlap"));
}
