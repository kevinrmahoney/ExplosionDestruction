// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "EDFire.generated.h"

class UPaperSpriteComponent;
class UBoxComponent;
class AEDFireStarter;
class AEDCharacter;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDFire : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDFire();

	UFUNCTION()
	void AddFuel(float Fuel);

protected:

	UPROPERTY(EditAnywhere, Category = "Components")
	UPaperSpriteComponent* SpriteComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* HeatArea;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* FireArea;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* EngulfedArea;

	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* InstantDeathArea;


	UPROPERTY(EditAnywhere)
	float StartingSpeed = 300.f;

	UPROPERTY(EditAnywhere)
	float MinSpeed = 100.f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 1000.f;

	UPROPERTY(EditAnywhere)
	FVector Direction = FVector(1.f, 0.f, 0.f);

	UPROPERTY(EditAnywhere)
	float HeatDamagePerSecond = 5.f;

	UPROPERTY(EditAnywhere)
	float FireDamagePerSecond = 20.f;

	UPROPERTY(EditAnywhere)
	float EngulfedDamagePerSecond = 30.f;

	UPROPERTY()
	float Speed = 0.f;

	UPROPERTY()
	float Fuel = 0.f;

	UPROPERTY()
	bool Started = false;

	UPROPERTY()
	TArray<AActor*> OnHeatArray;

	UPROPERTY()
	TArray<AActor*> OnFireArray;

	UPROPERTY()
	TArray<AActor*> OnEngulfedArray;



	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHeatBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHeatEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnFireBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnFireEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnEngulfedBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEngulfedEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnInstantDeathBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Start();

	void Initialize(FVector InitLocation, FRotator InitRotation, float InitFuel, float InitSpeed);

};
