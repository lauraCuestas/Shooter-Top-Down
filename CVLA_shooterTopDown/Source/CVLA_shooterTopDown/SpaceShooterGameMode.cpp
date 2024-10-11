// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceShooterGameMode.h"
#include "GameWidget.h"


ASpaceShooterGameMode::ASpaceShooterGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	Score = 0;
	MIN_TIME_SPAWN = 0.5f;
	MAX_TIME_SPAWN = 2.5f;
	TIME_TO_MAX_DIFF = 60.0f;
}


void ASpaceShooterGameMode::BeginPlay()
{
	Super::BeginPlay();

	ChangeMenuWidget(StartingWidgetClass);
	((UGameWidget*)CurrentWidget)->Load();
}

void ASpaceShooterGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),NewWidgetClass);

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void ASpaceShooterGameMode::IncrementScore()
{
	Score += 10;
	((UGameWidget*)CurrentWidget)->SetScore(Score);
}

void ASpaceShooterGameMode::GameOver()
{
	((UGameWidget*)CurrentWidget)->OnGameOver(Score);
}

void ASpaceShooterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	GameTimer += DeltaTime; //Vamos gardando o tempo total do xogo
	EnemyTimer -= DeltaTime; //Contador decrecente

	if (EnemyTimer <= 0.0f) {
		float DiffPercentage = FMath::Min(GameTimer / TIME_TO_MAX_DIFF, 1.0f);
		EnemyTimer = MAX_TIME_SPAWN - (MAX_TIME_SPAWN - MIN_TIME_SPAWN) * DiffPercentage;
		UWorld* World = GetWorld();
		if (World) {
			FVector NewLocation = FVector(600.0f, FMath::RandRange(-700.0f, 700.0f), 70.0f);
			World->SpawnActor<AEnemy>(Enemy_Blueprint, NewLocation, FRotator::ZeroRotator);
		}	
		//Debo xerar un novo inimigo
		//Debo decidir canto tempo debe pasar ata o próximo inimigo
	}

}


