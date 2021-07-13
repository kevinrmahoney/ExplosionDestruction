// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EDCharacter.generated.h"

class UBoxComponent;
class AEDWeapon;
class UEDBaseHUD;
class UEDHealthComponent;
class USceneComponent;
class UCreatureMeshComponent;

#define FACING_RIGHT 1.f
#define FACING_LEFT -1.f

USTRUCT(BlueprintType)
struct FControllerInput
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TryJump = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TryMoveLeft = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TryMoveRight = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TryShoot = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool TryWallKick = false;
};

USTRUCT(BlueprintType)
struct FCharacterState
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsJumping = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsMoving = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsFalling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsWallKicking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsGrounded = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsShooting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool CanWallKick = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Rotation = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int JumpCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Velocity = FVector::ZeroVector;
};

// Represents each Animation State. IMPORTANT: The names of these enums MUST match
// the names in the Creature Animation Asset! If the enum does not match EXACTLY
// the animation name in the Creature Animation Asset, it will not switch to the animation
// in our animataion state machine.
UENUM(BlueprintType)
enum EAnimationState
{
	Idle,
	Walk,
	Jump,
	Falling,
	Land,
	WallSlide,
	WallKick,
	Slide,
	Sliding,
	SlideJump
};

/**
 * This class is the default character for ExplosionDestruction, and it is responsible for all
 * physical interaction between the player and the world.
 *
 * The capsule component (inherited from ACharacter) handles collision with the world
 * The CharacterMovementComponent (inherited from ACharacter) handles movement of the collision capsule
 * The Sprite component (inherited from APaperCharacter) handles the visuals
 */
UCLASS(config=Game)
class AEDCharacter : public APaperCharacter
{
	GENERATED_BODY()

	enum Weapon
	{
		None,
		RocketLauncher,
		GrenadeLauncher,
		AssaultRifle
	};

public:
	AEDCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Called for side to side input */
	void MoveRightBegin();
	void MoveRightEnd();
	void MoveLeftBegin();
	void MoveLeftEnd();

	// Shooting binds
	void SetShootBegin();
	void SetShootEnd();

	// Jumping binds
	void SetJumpBegin();
	void SetJumpEnd();

	// Equip binds
	void EquipRocketLauncher();
	void EquipGrenadeLauncher();
	void EquipAssaultRifle();

	// Wall Kick Overlap Events
	// Top
	UFUNCTION()
	void OnWallKickTopComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWallKickTopComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Bottom
	UFUNCTION()
	void OnWallKickBottomComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWallKickBottomComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Left
	UFUNCTION()
	void OnWallKickLeftComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWallKickLeftComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Right
	UFUNCTION()
	void OnWallKickRightComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnWallKickRightComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Getters
	UFUNCTION(BlueprintCallable)
	float GetAmmo();

	UFUNCTION(BlueprintCallable)
	float GetSpeed();

	// Equipped Weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bHasRocketLauncher = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bHasGrenadeLauncher = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bHasAssaultRifle = true;

private:
	// Movement
	bool DoMove(float DeltaSeconds);

	// Shoot currently held weapon
	bool DoShootWeapon(float DeltaSeconds);

	// Jump off ground
	bool DoJump(float DeltaSeconds);

	// Wall kick
	bool DoWallKick(float DeltaSeconds);

	// Initialize
	void InitializeHUD();
	void InitializeDynamicEvents();

	// Updates the HUD (if needed)
	void UpdateHUD();

	// Update state of character
	void UpdateState();

	// Updates Character variables
	void UpdateCharacter();

	// Equip a new weapon (potentially)
	void EquipWeapon(enum Weapon NewWeapon);

protected:

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class UCreatureMeshComponent* CreatureMeshComponent;

	/* HUD */
	UPROPERTY(EditAnywhere, Category = HUD)
	TSubclassOf<class UEDBaseHUD> BaseHUDClass;
	class UEDBaseHUD* BaseHUD;

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;


	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/* Wall Kick Collision Boxes */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UBoxComponent* WallKickTopComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UBoxComponent* WallKickBottomComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UBoxComponent* WallKickLeftComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UBoxComponent* WallKickRightComponent;


	/* Movement parameters */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	float WallKickSpeed = 800;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	int MaxJumpCount = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Movement)
	int JumpSpeed = 1000.f;


	/* Animations */

	// The animation to play while running around
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* RunningAnimation;

	// The animation to play while idle (standing still)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* IdleAnimation;

	// The animation to play while jumping
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* JumpingAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	float JumpingAnimationMaxDuration;

	// The animation to play while hanging of a wall/ledge
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* HangingAnimation;

	// The animation to play while falling
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UPaperFlipbook* FallingAnimation;

	/** Called to choose the correct animation to play based on the character's movement state */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "Update Animation"))
	void UpdateAnimation(float DeltaSeconds);

	float AnimationDuration = 0.f;

	/* Weapons */
	enum Weapon EquippedWeapon = None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	AEDWeapon* CurrentWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pivots)
	USceneComponent* WeaponPivotPoint;

	UPROPERTY(EditAnywhere, Category = Weapons)
	TSubclassOf<class AEDWeapon> RocketLauncherClass;

	UPROPERTY(EditAnywhere, Category = Weapons)
	TSubclassOf<class AEDWeapon> GrenadeLauncherClass;

	UPROPERTY(EditAnywhere, Category = Weapons)
	TSubclassOf<class AEDWeapon> AssaultRifleClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapons)
	FName WeaponSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	UEDHealthComponent* HealthComp;

	UFUNCTION()
	void EDOnHealthChanged(UEDHealthComponent* OwnedHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void EDOnDeath(AActor* DestroyedActor);

	/* Blueprint Implementable Events (for sounds, graphics, etc) */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn"))
	void EDOnSpawnBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Death"))
	void EDOnDeathBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Health Changed"))
	void EDOnHealthChangedBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Jump"))
	void EDOnJumpBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Wall Kick"))
	void EDOnWallKickBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Landed"))
	void EDOnLandedBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Damage Taken"))
	void EDOnDamageTakenBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Slide Begin"))
	void EDOnSlideBeginBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Slide End"))
	void EDOnSlideEndBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Walk Begin"))
	void EDOnWalkBeginBP();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Walk End"))
	void EDOnWalkEndBP();

	// Character states. The current state, and the state from the previous tick
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCharacterState PreviousState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCharacterState CurrentState;

	// Player Input current state
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FControllerInput CurrentInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EAnimationState> CurrentAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EAnimationState> PreviousAnimation;

	// Counters
	float Ammo = 10.f;

	// If we should update the HUD on next tick
	bool ShouldUpdateHUD = false;

	// If we are overlapping objects to our left, right, top, bottom of character.
	bool OverlapLeft = false;
	bool OverlapRight = false;
	bool OverlapTop = false;
	bool OverlapBottom = false;

	// Represents the actively set vectors available to wall kick off.
	FVector WallKickVectorsAvailable = FVector::ZeroVector;
};
