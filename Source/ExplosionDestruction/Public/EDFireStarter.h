// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EDFire.h"
#include "Components/SceneComponent.h"

#include "EDFireStarter.generated.h"

class AEDFire;

UCLASS()
class EXPLOSIONDESTRUCTION_API AEDFireStarter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEDFireStarter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Fire)
	AEDFire* TriggeredFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Fire)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Fire)
	UBoxComponent* TriggerArea;

	UFUNCTION()
	void OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
