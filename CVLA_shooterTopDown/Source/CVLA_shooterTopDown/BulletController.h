// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletController.generated.h"

UCLASS()
class CVLA_SHOOTERTOPDOWN_API ABulletController : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UShapeComponent* RootBox;

	UPROPERTY(EditAnywhere)
		float Speed;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlapedComponent,
			AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32
			OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
