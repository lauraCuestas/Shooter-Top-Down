// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpaceShipController.generated.h"

UCLASS()
class CVLA_SHOOTERTOPDOWN_API ASpaceShipController : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpaceShipController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		float Speed;

	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	UPROPERTY(EditAnywhere, Category = "Spawing")
		TSubclassOf<class ABulletController>BulletBlueprint;

	void OnShootPress();

	FVector CurrentVelocity;

	bool Died;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnResetPress();

};


