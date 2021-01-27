// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EDCharacter.generated.h"

class UBoxComponent;
class AEDWeapon;
class UEDBaseHUD;
class UEDHealthComponent;

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

public:
	AEDCharacter();

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Called for side to side input */
	void SetMoving(float Value);

	void SetShooting(bool NewShooting);

	void SetJumping(bool NewJumping);

	UFUNCTION(BlueprintCallable)
	float GetAmmo();

	UFUNCTION(BlueprintCallable)
	float GetSpeed();

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

protected:

	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/* HUD */
	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<class UEDBaseHUD> BaseHUDClass;
	class UEDBaseHUD* BaseHUD;

	// Updates the HUD (if needed)
	void UpdateHUD();


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
	int MaxJumpCount = 2;

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
	void OnHealthChanged(UEDHealthComponent* OwnedHealthComp, float Health, float HealthDelta, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION()
	void HandleEndPlay(AActor* Actor, EEndPlayReason::Type EndPlayReason);

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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool EventBeginWalk();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool EventEndWalk();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool EventWalk();

// States
	bool Jumping = false;
	bool Shooting = false;
	bool Falling = false;
	bool WallKicking = false;
	bool Grounded = true;
	FVector MovementInput = FVector::ZeroVector;
	float Facing = 1.f; // 1.f if facing right, -1.f if facing left.
	bool CanWallKick = false; // can only wall kick when we get close to a new wall
	int JumpCount = 0;
	bool Jumped = false; // If we actually jumped
	float Ammo = 10.f;
	bool bUpdateHUD = false;
	FVector OldVelocity = FVector::ZeroVector;
	UPROPERTY(BlueprintReadOnly, Category = "Player")
	bool bDied;

	// If we are overlapping objects to our left, right, top, bottom of character.
	bool OverlapLeft = false;
	bool OverlapRight = false;
	bool OverlapTop = false;
	bool OverlapBottom = false;

	// Represents the actively set vectors available to wall kick off.
	FVector WallKickVectorsAvailable = FVector::ZeroVector;
};
