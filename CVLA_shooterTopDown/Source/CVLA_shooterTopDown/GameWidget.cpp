// Fill out your copyright notice in the Description page of Project Settings.


#include "GameWidget.h"

void UGameWidget::Load()
{
	const FName TextBlockName = FName(TEXT("GameTextBlock"));
	if (ScoreTextBlock == nullptr)
	{
		ScoreTextBlock = (UTextBlock*)(WidgetTree->FindWidget(TextBlockName));
	}
}

void UGameWidget::SetScore(int score)
{
	if (ScoreTextBlock != nullptr)
	{
		ScoreTextBlock -> SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score)));
	}
}

void UGameWidget::OnGameOver(int score)
{
	if (ScoreTextBlock != nullptr)
	{
		ScoreTextBlock -> SetText(FText::FromString(FString(TEXT("Score: ")) + FString::FromInt(score) + TEXT("\n Pulsa R para reiniciar")));
	}
}
