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
#include "Logger.h"
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
	WallKickBottomComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickBottomComponent"));
	WallKickLeftComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickLeftComponent"));
	WallKickRightComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("WallKickRightComponent"));

	if(WallKickTopComponent && WallKickBottomComponent && WallKickRightComponent && WallKickLeftComponent)
	{
		WallKickRightComponent->SetupAttachment(GetCapsuleComponent());
		WallKickLeftComponent->SetupAttachment(GetCapsuleComponent());
		WallKickBottomComponent->SetupAttachment(GetCapsuleComponent());
		WallKickTopComponent->SetupAttachment(GetCapsuleComponent());
	}
	else
		Logger::Error(TEXT("Failed to create wall kick components!"));


	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));

	if(CameraBoom)
	{
		CameraBoom->SetupAttachment(RootComponent);
		CameraBoom->TargetArmLength = 500.0f;
		CameraBoom->SocketOffset = FVector(0.0f, 0.0f, 75.0f);
		CameraBoom->SetUsingAbsoluteRotation(true);
		CameraBoom->bDoCollisionTest = false;
		CameraBoom->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		CameraBoom->SetUsingAbsoluteRotation(true);
	}
	else
		Logger::Error(TEXT("Failed to create camera boom!"));


	// Create an orthographic camera (no perspective) and attach it to the boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));

	if(SideViewCameraComponent)
	{
		SideViewCameraComponent->ProjectionMode = ECameraProjectionMode::Orthographic;
		SideViewCameraComponent->OrthoWidth = 2048.0f;
		SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
		SideViewCameraComponent->bUsePawnControlRotation = false;
		SideViewCameraComponent->bAutoActivate = true;
	}
	else
		Logger::Error(TEXT("Failed to create side view camera!"));

	// Create component to manage health
	HealthComp = CreateDefaultSubobject<UEDHealthComponent>(TEXT("HealthComp"));
	
	if(HealthComp)
		HealthComp->SetMaxHealth(100.f);

	// Configure character movement
	GetCharacterMovement()->GravityScale = 2.0f;
	GetCharacterMovement()->AirControl = 1.8f;
	GetCharacterMovement()->JumpZVelocity = 800.f;
	GetCharacterMovement()->GroundFriction = 4.0f;
	GetCharacterMovement()->MaxWalkSpeed = 900.0f;
	GetCharacterMovement()->MaxFlySpeed = 600.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(44.f);
	GetCharacterMovement()->bOrientRotationToMovement = false;

	// Lock character motion onto the XZ plane, so the character can't move in or out of the screen
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->SetPlaneConstraintNormal(FVector(0.0f, -1.0f, 0.0f));

	// Behave like a traditional 2D platformer character, with a flat bottom instead of a curved capsule bottom
	// Note: This can cause a little floating when going up inclines; you can choose the tradeoff between better
	// behavior on the edge of a ledge versus inclines by setting this to true or false
	GetCharacterMovement()->bUseFlatBaseForFloorChecks = true;

	// Enable replication on the Sprite component so animations show up when networked
	GetSprite()->SetIsReplicated(true);

	WeaponPivotPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Weapon Pivot Point"));
	WeaponPivotPoint->AttachToComponent(GetCapsuleComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);

	bReplicates = true;

	JumpMaxCount = 1;
	JumpMaxHoldTime = 0.25f;
}

void AEDCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(!GetWorld())
		Logger::Error(TEXT("Could not get the World!"));

	if(!WallKickTopComponent || !WallKickBottomComponent || !WallKickLeftComponent || !WallKickRightComponent)
		Logger::Error(TEXT("Could not create one or more of the Wall Kick Components!"));

	if(!HealthComp)
		Logger::Error(TEXT("Could not create Health Component!"));

	// Make sure weapon classes are specified
	if(!RocketLauncherClass || !GrenadeLauncherClass || !AssaultRifleClass)
	{
		Logger::Error(TEXT("One or more weapon classes are unspecified for this character! Check the blueprint!"));
	}

	EquipWeapon(RocketLauncher);

	// Facing right by default
	CurrentState.Rotation = FACING_RIGHT;

	// Initialize the character's HUD
	InitializeHUD();

	// Add any dynamic events.
	InitializeDynamicEvents();

	EDOnSpawnBP();
}

// Call this to initialize the HUD
void AEDCharacter::InitializeHUD()
{
	// Create the HUD if it doesn't already exist.
	if(BaseHUDClass)
	{
		BaseHUD = CreateWidget<UEDBaseHUD>(GetWorld(), BaseHUDClass);
	}
	else
	{
		Logger::Error(TEXT("Failed to create HUD! Make sure the character BP has a HUD class assigned to it!"));
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
	if(HealthComp)
		HealthComp->OnHealthChanged.AddDynamic(this, &AEDCharacter::EDOnHealthChanged);
	else
		Logger::Error(TEXT("Could not add events to health component!"));

	OnDestroyed.AddDynamic(this, &AEDCharacter::EDOnDeath);
}


void AEDCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UpdateState();

	// Apply the input to the character motion from left/right input
	if(CurrentInput.TryMoveLeft || CurrentInput.TryMoveRight)
		CurrentState.IsMoving = DoMove(DeltaSeconds);

	// Fire weapon if we are firing
	if(CurrentInput.TryShoot && CurrentWeapon)
		CurrentState.IsShooting = DoShootWeapon(DeltaSeconds);

	// Try to perform a jump
	if(CurrentInput.TryJump)
	{
		// We can jump from the ground
		if(CurrentState.IsGrounded)
		{
			CurrentState.IsJumping = DoJump(DeltaSeconds);
		}
		// If we're in midair, we have two options
		else
		{
			// Do a wall kick before a double jump, if we can.
			if(CurrentState.CanWallKick && WallKickVectorsAvailable.SizeSquared())
			{
				CurrentState.IsWallKicking = DoWallKick(DeltaSeconds);

				if(CurrentState.IsWallKicking)
					CurrentInput.TryWallKick = false;
			}
			// Do a double jump as a last resort, if we can
			else if(CurrentState.JumpCount < MaxJumpCount)
			{
				CurrentState.IsJumping = DoJump(DeltaSeconds);
			}
		}

		// Whether or not we succeeded in jumping, we cant try again until the jump button is clicked.
		CurrentInput.TryJump = false;
	}

	// Update animation to match the motion
	UpdateAnimation(DeltaSeconds);

	// Update some character stuff
	UpdateCharacter();

	// Update the HUD
	if(ShouldUpdateHUD)
		UpdateHUD();

	// Save the previous state
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
	// Shoot the currently held weapon
	bool IsShooting = false;

	if(CurrentWeapon)
	{
		if(CurrentInput.TryShoot)
			IsShooting = CurrentWeapon->PullTrigger();

		if(!CurrentInput.TryShoot)
			IsShooting = CurrentWeapon->ReleaseTrigger();
	}

	// We should udpate the HUD if we shot (ammo count)
	if(IsShooting)
		ShouldUpdateHUD = true;

	return IsShooting;
}

bool AEDCharacter::DoJump(float DeltaSeconds)
{
	// We can jump if we are on the ground and trying to jump
	CurrentState.JumpCount++;
	GetCharacterMovement()->Velocity.Z = JumpSpeed;
	GetCharacterMovement()->SetMovementMode(MOVE_Falling); // If we don't do this, the movement isn't applied.
	ShouldUpdateHUD = true; // Our speed changes
	EDOnJumpBP(); // Trigger jump event

	Logger::Verbose(TEXT("Character %s jumped"), *GetName());

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

	EDOnWallKickBP();

	Logger::Verbose(TEXT("Character %s wallkicked with velocity %s (%f)"), *GetName(), *WallKickDeltaV.ToString(), WallKickDeltaV.Size());

	return true;
}

//
// Updaters
//

void AEDCharacter::UpdateCharacter()
{
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
	WallKickVectorsAvailable = FVector::ZeroVector;

	// Get current states
	CurrentState.Velocity = GetVelocity();

	// Set if we're moving
	CurrentState.IsMoving = CurrentState.Velocity.IsNearlyZero();

	// Check if character has begun walking or ended walking
	if(PreviousState.Velocity.IsNearlyZero() && !CurrentState.Velocity.IsNearlyZero())
		EDOnWalkBeginBP();
	else if(!PreviousState.Velocity.IsNearlyZero() && CurrentState.Velocity.IsNearlyZero())
		EDOnWalkEndBP();

	// Set if the character is on the grounded
	CurrentState.IsFalling = GetCharacterMovement()->IsFalling();
	CurrentState.IsGrounded = !CurrentState.IsFalling;

	// If the character has landed after being in air.
	if(CurrentState.IsGrounded && PreviousState.IsFalling)
		EDOnLandedBP();

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

	// If we can still wall kick because we *were* near a wall but are no longer
	// near one, then we can't wall kick. Need to get near a wall again.
	if(CurrentState.CanWallKick && WallKickVectorsAvailable.IsNearlyZero())
	{
		CurrentState.CanWallKick = false;
	}

	// If the character has landed after being in air.
	if(CurrentState.IsGrounded && PreviousState.IsFalling)
		EDOnLandedBP();
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

	if(CurrentWeapon)
	{
		// Now lets update the weapon animation (where its pointing)
		FVector ActorLocation = GetActorLocation();
		FVector MouseWorldLocation;
		FVector MouseWorldDirection;
		FVector Target;

		// Get location of the mouse cursor. Make sure to remove the Y component since this is 2D
		ActorLocation.Y = 0.f;
		GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(MouseWorldLocation, MouseWorldDirection);
		MouseWorldLocation.Y = 0.f;
		Target = (MouseWorldLocation - ActorLocation);
		CurrentWeapon->SetActorRotation(Target.Rotation());
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

// Equip new weapon
void AEDCharacter::EquipWeapon(enum Weapon NewWeapon)
{
	// Don't equip a new weapon if its the same as the old one
	if(NewWeapon == EquippedWeapon)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = this;

	// Destroy the current weapon before making a new one.
	if(CurrentWeapon)
	{
		Logger::Verbose(TEXT("Character %s's weapon %s is being destroyed."), *GetName(), *CurrentWeapon->GetName());
		CurrentWeapon->Destroy();
		CurrentWeapon = nullptr;
	}

	// Create the requested weapon and save the pointer for later use.
	if(NewWeapon == RocketLauncher)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AEDWeapon>(RocketLauncherClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
	else if(NewWeapon == GrenadeLauncher)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AEDWeapon>(GrenadeLauncherClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
	else if(NewWeapon == AssaultRifle)
	{
		CurrentWeapon = GetWorld()->SpawnActor<AEDWeapon>(AssaultRifleClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
	}
	else
	{
		Logger::Error(TEXT("Character %s has attempted to equip a weapon that doesnt exist."), *GetName());
		return;
	}

	// Make sure to set the owner.
	if(CurrentWeapon)
	{
		CurrentWeapon->SetOwner(this);
		CurrentWeapon->PivotPoint->SetupAttachment(WeaponPivotPoint);
		CurrentWeapon->AttachToComponent(WeaponPivotPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
		//CurrentWeapon->AttachToComponent(WeaponPivotPoint, FAttachmentTransformRules::KeepWorldTransform);
		EquippedWeapon = NewWeapon;
		Logger::Verbose(TEXT("THIS IS BULLSHIT: %s"), *WeaponPivotPoint->GetComponentLocation().ToString());

		Logger::Verbose(TEXT("Character %s has equipped weapon %s."), *GetName(), *CurrentWeapon->GetName());
	}
}

//
// Events
//

// Called on damage recieved or healing received
void AEDCharacter::EDOnHealthChanged(UEDHealthComponent* OwnedHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	EDOnHealthChangedBP();

	if(Health <= 0.f && !CurrentState.IsDead)
	{
		// die
		CurrentState.IsDead = true;

		GetMovementComponent()->StopMovementImmediately();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		DetachFromControllerPendingDestroy();

		SetLifeSpan(3.f);

		Destroy();
	}
}

// Called on death of character
void AEDCharacter::EDOnDeath(AActor* DestroyedActor)
{
	// Remove the HUD related to this character from the player's screen.
	if(BaseHUD)
		BaseHUD->Remove();

	// If we die, we should reset the CurrentInput
	CurrentInput = PlayerInput();

	if(CurrentWeapon)
	{
		// Let go of the trigger
		CurrentWeapon->ReleaseTrigger();
		CurrentWeapon->Destroy();
	}

	Logger::Verbose(TEXT("Character %s has died!"), *GetName());

	EDOnDeathBP();
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

float AEDCharacter::GetAmmo()
{
	return Ammo;
}

float AEDCharacter::GetSpeed()
{
	return CurrentState.Velocity.Size();
}

//
// Input Handling
//

void AEDCharacter::SetShootBegin()
{
	CurrentInput.TryShoot = true;
}

void AEDCharacter::SetShootEnd()
{
	CurrentInput.TryShoot = false;
}

void AEDCharacter::SetJumpBegin()
{
	CurrentInput.TryJump = true;
}

void AEDCharacter::SetJumpEnd()
{
	CurrentInput.TryJump = false;
}

void AEDCharacter::MoveRightBegin()
{
	// Try to move right
	CurrentInput.TryMoveRight = true;
}

void AEDCharacter::MoveRightEnd()
{
	// Stop trying to move right
	CurrentInput.TryMoveRight = false;
}

void AEDCharacter::MoveLeftBegin()
{
	// Try to move left
	CurrentInput.TryMoveLeft = true;
}

void AEDCharacter::MoveLeftEnd()
{
	// Stop trying to move left
	CurrentInput.TryMoveLeft = false;
}

// These methods equip weapons.
void AEDCharacter::EquipRocketLauncher()
{
	EquipWeapon(RocketLauncher);
}

void AEDCharacter::EquipGrenadeLauncher()
{
	EquipWeapon(GrenadeLauncher);
}

void AEDCharacter::EquipAssaultRifle()
{
	EquipWeapon(AssaultRifle);
}
