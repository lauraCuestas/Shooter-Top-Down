// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletController.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "SpaceShooterGameMode.h"


// Sets default values
ABulletController::ABulletController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 300.0f;
	PrimaryActorTick.bCanEverTick = true;
	RootBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));

	RootBox->SetGenerateOverlapEvents(true);
	RootBox->OnComponentBeginOverlap.AddDynamic(this,&ABulletController::OnOverlap);

}

// Called when the game starts or when spawned
void ABulletController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABulletController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	NewLocation.X = NewLocation.X + Speed * DeltaTime;
	SetActorLocation(NewLocation);

	if (NewLocation.X > 700.0f) {
		this->Destroy();
	}
}

void ABulletController::OnOverlap(UPrimitiveComponent* OverlapedComponent, AActor* OtherActor, UPrimitiveComponent*
	OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor->IsA(AEnemy::StaticClass())) {
		this->Destroy();
		OtherActor->Destroy();

		((ASpaceShooterGameMode*)GetWorld() -> GetAuthGameMode())->IncrementScore();
	}
}

