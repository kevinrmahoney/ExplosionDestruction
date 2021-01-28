// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EDCharacter.generated.h"

class UBoxComponent;
class AEDWeapon;
class UEDBaseHUD;
class UEDHealthComponent;

#define FACING_RIGHT 1.f
#define FACING_LEFT -1.f

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

private:
	struct CharacterState
	{
		bool IsJumping;
		bool IsMoving;
		bool IsFalling;
		bool IsWallKicking;
		bool IsGrounded;
		bool IsDead;
		bool IsShooting;
		bool CanWallKick;
		float Rotation;
		int JumpCount;
		FVector Velocity;
	};

	struct PlayerInput
	{
		bool TryJump;
		bool TryMoveLeft;
		bool TryMoveRight;
		bool TryShoot;
		bool TryWallKick;
	};

public:
	AEDCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Called for side to side input */
	void MoveRightPressed();
	void MoveRightReleased();
	void MoveLeftPressed();
	void MoveLeftReleased();

	// Shooting binds
	void SetShootingPressed();
	void SetShootingReleased();

	// Jumping binds
	void SetJumpingPressed();
	void SetJumpingReleased();

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

private:
	// Movement
	bool DoMove(float DeltaSeconds);

	// Shoot currently held weapon
	bool DoShootWeapon(float DeltaSeconds);

	// Jump off ground
	bool DoJump(float DeltaSeconds);

	// Wall kick
	bool DoWallKick(float DeltaSeconds);

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	void InitializeHUD();
	void InitializeDynamicEvents();

	/* HUD */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UEDBaseHUD> BaseHUDClass;
	class UEDBaseHUD* BaseHUD;

	// Updates the HUD (if needed)
	UFUNCTION(BlueprintCallable)
	void UpdateHUD();

	void UpdateState();

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Animations)
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
	void UpdateAnimation(float DeltaSeconds);

	float AnimationDuration = 0.f;

	// Updates Character variables
	void UpdateCharacter();

	/* Weapons */
	AEDWeapon* CurrentWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Weapons)
	TSubclassOf<AEDWeapon> StarterWeaponClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Weapons)
	FName WeaponSocketName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UEDHealthComponent* HealthComp;

	/* Blueprint Implementable Events (for sounds, graphics, etc) */
	UFUNCTION()
	void EDOnHealthChanged(UEDHealthComponent* OwnedHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void EDOnDeath(AActor* Actor, EEndPlayReason::Type EndPlayReason);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Jump"))
	void EDOnJump();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Wall Kick"))
	void EDOnWallKick();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Landed"))
	void EDOnLanded();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Damage Taken"))
	void EDOnDamageTaken();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Slide Begin"))
	void EDOnSlideBegin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Slide End"))
	void EDOnSlideEnd();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Walk Begin"))
	bool EDWalkBegin();

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Walk End"))
	bool EDWalkEnd();

	// Character states
	CharacterState PreviousState;
	CharacterState CurrentState;

	// Player Input states
	PlayerInput CurrentInput;

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
