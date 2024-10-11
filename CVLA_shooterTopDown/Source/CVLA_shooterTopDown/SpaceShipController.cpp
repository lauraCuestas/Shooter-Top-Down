// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShipController.h"
#include "BulletController.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Enemy.h"
#include "spaceShooterGameMode.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
ASpaceShipController::ASpaceShipController()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Speed = 10.0f;

	CollisionBox->SetGenerateOverlapEvents(true);

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASpaceShipController::OnOverlap);
}

// Called when the game starts or when spawned
void ASpaceShipController::BeginPlay()
{
	Super::BeginPlay();
}

void ASpaceShipController::Move_XAxis(float AxisValue) 
{
	CurrentVelocity.X = AxisValue * 100.0f;
}

void ASpaceShipController::Move_YAxis(float AxisValue) 
{
	CurrentVelocity.Y = AxisValue * 100.0f;
}

void ASpaceShipController::OnShootPress() 
{
	UWorld* World = GetWorld(); //referencia á escena
		if (World) {
			FVector Location = GetActorLocation();
			World->SpawnActor<ABulletController>(BulletBlueprint,Location, FRotator::ZeroRotator);
		}
}

void ASpaceShipController::OnResetPress()
{
	if (Died)
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld() -> GetName()), false);
		//Abrimos de novo o nivel (collemos o nome do mundo) e reseteamos todas as variables do nivel co parámetro "false"
	}
}

void ASpaceShipController::OnOverlap(UPrimitiveComponent*OverlapedComponent, AActor* OtherActor, UPrimitiveComponent*
	OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
			if (OtherActor->IsA(AEnemy::StaticClass())) {
				Died = true;
				this->SetActorHiddenInGame(true);
				UGameplayStatics::SetGamePaused(GetWorld(), true);
			}
	}

// Called every frame
void ASpaceShipController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CurrentVelocity.IsZero()) {
		FVector NewLocation = GetActorLocation() + Speed * CurrentVelocity * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void ASpaceShipController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &ASpaceShipController::Move_XAxis);

	PlayerInputComponent->BindAxis("MoveY", this, &ASpaceShipController::Move_YAxis);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ASpaceShipController::OnShootPress);

	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &ASpaceShipController::OnResetPress).bExecuteWhenPaused = true;
}

