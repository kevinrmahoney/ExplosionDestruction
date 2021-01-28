// Copyright Epic Games, Inc. All Rights Reserved.

#include "EDCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EDWeapon.h"
#include "Components/BoxComponent.h"
#include "EDBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "EDHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(SideScrollerCharacter, Log, All);

//
// EDCharacter
//

AEDCharacter::AEDCharacter()
{
	// Use only Yaw from the controller and ignore the rest of the rotation.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Set the size of our collision capsule.
	GetCapsuleComponent()->SetCapsuleHalfHeight(96.0f);
	GetCapsuleComponent()->SetCapsuleRadius(40.0f);

	// Hit boxes for the wallkicks. Attach to the capsule so we don't rotate with the sprite
	WallKickTopComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickTopComponent"));
	WallKickTopComponent->SetupAttachment(GetCapsuleComponent());

	WallKickBottomComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickBottomComponent"));
	WallKickBottomComponent->SetupAttachment(GetCapsuleComponent());

	WallKickLeftComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickLeftComponent"));
	WallKickLeftComponent->SetupAttachment(GetCapsuleComponent());

	WallKickRightComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickRightComponent"));
	WallKickRightComponent->SetupAttachment(GetCapsuleComponent());

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

	// Create component to manage health
	HealthComp = CreateDefaultSubobject<UEDHealthComponent>(TEXT("HealthComp"));

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
	JumpMaxCount = 1;
	JumpMaxHoldTime = 0.25f;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);
	bReplicates = true;
}

void AEDCharacter::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;

	CurrentWeapon = GetWorld()->SpawnActor<AEDWeapon>(StarterWeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	if(CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}

	// Facing right by default
	CurrentState.Rotation = FACING_RIGHT;

	// Initialize the character's HUD
	InitializeHUD();

	// Add any dynamic events.
	InitializeDynamicEvents();
}

// Call this to initialize the HUD
void AEDCharacter::InitializeHUD()
{
	// Create the HUD if it doesn't already exist.
	if(BaseHUDClass != nullptr)
	{
		BaseHUD = CreateWidget<UEDBaseHUD>(GetWorld(), BaseHUDClass);
	}

	// Give the HUD a character reference so it can update character specific
	// HUD values, then add to the player viewport, then make sure it updates
	// on the next tick.
	if(BaseHUD)
	{
		BaseHUD->SetCharacter(this);
		BaseHUD->AddToViewport();
		ShouldUpdateHUD = true;
	}
}

// Put add dynamic event registration here.
void AEDCharacter::InitializeDynamicEvents()
{
	// Add event for each of the wallkick box components. Need to be in BeginPlay for some reason?
	WallKickTopComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickTopComponentBeginOverlap);
	WallKickTopComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickTopComponentEndOverlap);
	WallKickBottomComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickBottomComponentBeginOverlap);
	WallKickBottomComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickBottomComponentEndOverlap);
	WallKickLeftComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickLeftComponentBeginOverlap);
	WallKickLeftComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickLeftComponentEndOverlap);
	WallKickRightComponent->OnComponentBeginOverlap.AddDynamic(this, &AEDCharacter::OnWallKickRightComponentBeginOverlap);
	WallKickRightComponent->OnComponentEndOverlap.AddDynamic(this, &AEDCharacter::OnWallKickRightComponentEndOverlap);

	// Subscribe to health changed event
	HealthComp->OnHealthChanged.AddDynamic(this, &AEDCharacter::EDOnHealthChanged);

	// Add event to handle death
	OnEndPlay.AddDynamic(this, &AEDCharacter::EDOnDeath);
}


void AEDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateState();

	// Apply the input to the character motion from left/right input
	if(CurrentInput.TryMoveLeft || CurrentInput.TryMoveRight)
		DoMove(DeltaSeconds);

	// Fire weapon if we are firing
	if(CurrentInput.TryShoot && CurrentWeapon)
		CurrentState.IsShooting = DoShootWeapon(DeltaSeconds);
	else
		CurrentState.IsShooting = false;

	// Apply an impulse to the character from wall kicks, if applicable.
	// Wall kicks are impulses added to the character depending on the walls
	// they are in close contact with. This is determined by the
	// WallKickBoxComponent hitboxes above, below, to the left and right of
	// the character. Wall kicks should always add an impulse upwards (unless
	// touching a ceiling, where instead the impulse goes downwards) and add
	// an additional impulse in the direction opposite of the wall they're
	// touching.
	if((CurrentState.IsGrounded && CurrentInput.TryJump) || (CurrentState.IsFalling && CurrentState.JumpCount < MaxJumpCount))
	{
		DoJump(DeltaSeconds);
	}
	else if(CurrentState.IsFalling && CurrentInput.TryJump && CurrentState.CanWallKick && WallKickVectorsAvailable.SizeSquared() != 0.f)
	{
		DoWallKick(DeltaSeconds);
	}

	// Update animation to match the motion
	UpdateAnimation(DeltaSeconds);
	UpdateCharacter();
	UpdateHUD();

	PreviousState = CurrentState;
}

// Move the character left or right.
// By default, pressing both left and right
// cancels each other out.
bool AEDCharacter::DoMove(float DeltaSeconds)
{
	FVector MovementVector = FVector::ZeroVector;

	// Process user input to determine vector
	if(CurrentInput.TryMoveLeft)
		MovementVector.X += -1.f;
	if(CurrentInput.TryMoveRight)
		MovementVector.X += 1.f;

	// Update which way the sprite faces
	if(MovementVector.X > 0.f)
		CurrentState.Rotation = FACING_RIGHT;
	else if(MovementVector.X < 0.f)
		CurrentState.Rotation = FACING_LEFT;

	// Perform the movement to the character
	AddMovementInput(MovementVector, 1.f);

	return !MovementVector.IsNearlyZero();
}

bool AEDCharacter::DoShootWeapon(float DeltaSeconds)
{
	if(CurrentWeapon->Shoot())
	{
		ShouldUpdateHUD = true;
		return true;
	}
	else
		return false;
}

bool AEDCharacter::DoJump(float DeltaSeconds)
{
	// We can jump if we are on the ground and trying to jump
	CurrentState.JumpCount++;
	GetCharacterMovement()->Velocity.Z = JumpSpeed;
	GetCharacterMovement()->SetMovementMode(MOVE_Falling); // If we don't do this, the movement isn't applied.
	CurrentState.IsJumping = true;
	ShouldUpdateHUD = true; // Our speed changes
	EDOnJump(); // Trigger jump event

	return true;
}

bool AEDCharacter::DoWallKick(float DeltaSeconds)
{
	// This will serve as the change in velocity to apply the impulse.
	FVector WallKickDeltaV = FVector::ZeroVector;

	// When performing the wall jump, we first stop all movement in the directions
	// that we are hitting the walls from
	if(WallKickVectorsAvailable.X != 0.f)
		GetCharacterMovement()->Velocity.X = 0.f;

	if(WallKickVectorsAvailable.Z != 0.f)
		GetCharacterMovement()->Velocity.Z = 0.f;

	// Normalize the vectors available so we apply impulse in each direction equally
	// if we can wall kick off multiple walls
	WallKickVectorsAvailable.Normalize();

	// Add the WallKickSpeed vector in X direction, which points away from the walls the character is near
	WallKickDeltaV.X += (-1.f * WallKickVectorsAvailable.X * (WallKickSpeed));

	// Now, add the additional jump vector. If we're hitting our head, apply it in the negative
	// direction, simulating a jump off the ceiling
	if(WallKickVectorsAvailable.Z > 0.f)
		WallKickDeltaV.Z += -1.f * WallKickSpeed;
	else
		WallKickDeltaV.Z += WallKickSpeed;

	// Apply the total wallkick delta v
	GetCharacterMovement()->Velocity += WallKickDeltaV;

	// We can only wall kick once per wall. Reset when we get close to another wall
	CurrentState.CanWallKick = false;
	CurrentState.IsWallKicking = true;

	EDOnWallKick();

	return true;
}

//
// Updaters
//

void AEDCharacter::UpdateCharacter()
{
	// Set the rotation so that the character faces the direction they wish
	// to move
	if(Controller != nullptr)
	{
		if(CurrentState.Rotation < 0.f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if(CurrentState.Rotation > 0.f)
		{
			GetSprite()->SetRelativeRotation(FRotator(0.0, 0.0f, 0.0f));
		}
	}
}

void AEDCharacter::UpdateState()
{
	// Reset certain states before proceeding.
	CurrentState.IsJumping = false;
	CurrentState.IsMoving = false;
	CurrentState.IsFalling = false;
	CurrentState.IsWallKicking = false;
	CurrentState.IsGrounded = false;
	CurrentState.IsShooting = false;

	// Get current states
	CurrentState.Velocity = GetVelocity();

	CurrentState.IsMoving = CurrentState.Velocity.IsNearlyZero();

	// Check if character has begun walking or ended walking
	if(PreviousState.Velocity.IsNearlyZero() && !CurrentState.Velocity.IsNearlyZero())
		EDWalkBegin();
	else if(!PreviousState.Velocity.IsNearlyZero() && CurrentState.Velocity.IsNearlyZero())
		EDWalkEnd();

	// If the character has landed after being in air.
	if(CurrentState.IsGrounded && PreviousState.IsFalling)
		EDOnLanded();

	// Set if the character is on the grounded
	CurrentState.IsFalling = GetCharacterMovement()->IsFalling();
	CurrentState.IsGrounded = !CurrentState.IsFalling;

	// Reset JumpCount if we are on the ground
	if(CurrentState.IsGrounded)
		CurrentState.JumpCount = 0;
	// If we aren't on the ground and we haven't jumped yet, too bad, only get one jump in midair
	else if(CurrentState.JumpCount == 0)
		CurrentState.JumpCount = 1;

	// If the velocity has changed, we want to update the HUD.
	if(PreviousState.Velocity != CurrentState.Velocity)
		ShouldUpdateHUD = true;

	// Construct what wallkick vectors we have (if any) based on
	// what box components are overlapping the character.
	if(OverlapLeft)
		WallKickVectorsAvailable.X += -1.f;
	if(OverlapRight)
		WallKickVectorsAvailable.X += 1.f;
	if(OverlapTop)
		WallKickVectorsAvailable.Z += 1.f;
	if(OverlapBottom)
		WallKickVectorsAvailable.Z += -1.f;

	// One time where we force the character to face a different direction
	// is when the character is near a wall. This is due to the wall
	// hanging animation. So change direction depending on which side of the
	// character is near a wall.
	if(CurrentState.IsFalling && WallKickVectorsAvailable.X != 0.f)
	{
		if(WallKickVectorsAvailable.X < 0.f) // Wall to left, face right
			CurrentState.Rotation = FACING_RIGHT;
		else if(WallKickVectorsAvailable.X > 0.f) // Wall to right, face left
			CurrentState.Rotation = FACING_LEFT;
	}
}

void AEDCharacter::UpdateAnimation(float DeltaSeconds)
{
	const FVector PlayerVelocity = GetVelocity();
	const float PlayerSpeedSqr = PlayerVelocity.SizeSquared();

	UPaperFlipbook* DesiredAnimation;
	AnimationDuration += DeltaSeconds;

	// If we're jumping set that animation.
	if(CurrentState.IsJumping)
	{
		DesiredAnimation = JumpingAnimation;
	}
	// If we're on the ground, we can play idle or running animation
	else if(CurrentState.IsGrounded)
	{
		// Are we moving or standing still?
		DesiredAnimation = (PlayerSpeedSqr > 0.0f) ? RunningAnimation : IdleAnimation;
	}
	// If near a wall and falling, play the hanging animation
	else if(CurrentState.IsFalling && WallKickVectorsAvailable.X != 0)
	{
		DesiredAnimation = HangingAnimation;
	}
	// Otherwise, just play the falling animation
	else
	{
		DesiredAnimation = FallingAnimation;
	}

	// If we're not done playing the jump animation, continue to play it.
	if((GetSprite()->GetFlipbook() == JumpingAnimation && AnimationDuration < JumpingAnimationMaxDuration))
	{
		return;
	}

	// Set the animation
	if(GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
		AnimationDuration = 0.f;
	}
}

void AEDCharacter::UpdateHUD()
{
	if(BaseHUD)
	{
		BaseHUD->Update();
		ShouldUpdateHUD = false;
	}
}

//
// Events
//

void AEDCharacter::EDOnHealthChanged(UEDHealthComponent* OwnedHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Health <= 0.f && !CurrentState.IsDead)
	{
		// die
		CurrentState.IsDead = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		SetLifeSpan(3.f);
	}
}

void AEDCharacter::EDOnDeath(AActor* Actor, EEndPlayReason::Type EndPlayReason)
{
	// Remove the HUD related to this character from the player's screen.
	if(BaseHUD)
		BaseHUD->Remove();

	// Destroy the weapons they're holding.
	if(CurrentWeapon)
		CurrentWeapon->Destroy();
}

// Top
void AEDCharacter::OnWallKickTopComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == this)
		return;

	CurrentState.CanWallKick = OverlapTop = true;
}

void AEDCharacter::OnWallKickTopComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == this)
		return;

	OverlapTop = false;
}

// Bottom
void AEDCharacter::OnWallKickBottomComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == this)
		return;

	CurrentState.CanWallKick = OverlapBottom = true;
}

void AEDCharacter::OnWallKickBottomComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == this)
		return;

	OverlapBottom = false;
}

// Left
void AEDCharacter::OnWallKickLeftComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == this)
		return;

	CurrentState.CanWallKick = OverlapLeft = true;
}

void AEDCharacter::OnWallKickLeftComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == this)
		return;

	OverlapLeft = false;
}

// Right
void AEDCharacter::OnWallKickRightComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor == this)
		return;

	CurrentState.CanWallKick = OverlapRight = true;
}

void AEDCharacter::OnWallKickRightComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(OtherActor == this)
		return;

	OverlapRight = false;
}

//
// Getters / Setters
//

void AEDCharacter::SetShooting(bool NewShooting)
{
	CurrentInput.TryShoot = NewShooting;
}

void AEDCharacter::SetJumping(bool NewJumping)
{
	CurrentInput.TryJump = NewJumping;
}

float AEDCharacter::GetAmmo()
{
	return Ammo;
}

float AEDCharacter::GetSpeed()
{
	return GetCharacterMovement()->Velocity.Size();
}

void AEDCharacter::MoveRightPressed()
{
	// Try to move right
	CurrentInput.TryMoveRight = true;
}

void AEDCharacter::MoveRightReleased()
{
	// Stop trying to move right
	CurrentInput.TryMoveRight = false;
}

void AEDCharacter::MoveLeftPressed()
{
	// Try to move left
	CurrentInput.TryMoveLeft = true;
}

void AEDCharacter::MoveLeftReleased()
{
	// Stop trying to move left
	CurrentInput.TryMoveLeft = false;
}
