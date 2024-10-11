// Fill out your copyright notice in the Description page of Project Settings.


#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy.h"
#include "SpaceShooterGameMode.generated.h"

UCLASS()
class CVLA_SHOOTERTOPDOWN_API ASpaceShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AEnemy> Enemy_Blueprint;

	float EnemyTimer; //Cada canto tempo xero un inimigo
	float GameTimer; //O tempo de xogo

	ASpaceShooterGameMode();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Spawn")
		float MIN_TIME_SPAWN;
	UPROPERTY(EditAnywhere, Category = "Spawn")
		float MAX_TIME_SPAWN;
	UPROPERTY(EditAnywhere, Category = "Spawn")
		float TIME_TO_MAX_DIFF;

	UFUNCTION(BlueprintCallable) 
	void ChangeMenuWidget(TSubclassOf<UUserWidget>NewWidgetClass);

	void IncrementScore();
	void GameOver();

protected:
	virtual void BeginPlay() override;
	int Score = 0; //Puntuación. Variable que non é pública

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UUserWidget> StartingWidgetClass;

	UPROPERTY()
	UUserWidget* CurrentWidget;
	
};
