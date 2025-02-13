// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

#include "DodgeGameState.h"
#include "DodgePlayerCharacter.h"
#include "DodgePlayerController.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto GameState = GetWorld()->GetGameState<ADodgeGameState>())
	{
		UpdateTimerDisplay(GameState->GetRemainTime());
		GameState->OnTimeChangedDelegate.AddDynamic(this, &UHudWidget::UpdateTimerDisplay);

		UpdateScoreDisplay(GameState->GetScore());
		GameState->OnScoreChangedDelegate.AddDynamic(this, &UHudWidget::UpdateScoreDisplay);
	}

	if (ADodgePlayerController* PC = GetOwningPlayer<ADodgePlayerController>())
	{
		if (ACharacter* Character = PC->GetCharacter())
		{
			if (ADodgePlayerCharacter* DodgePlayerCharacter = Cast<ADodgePlayerCharacter>(Character))
			{
				UpdateLifeDisplay(DodgePlayerCharacter->GetLife());
				DodgePlayerCharacter->OnLifeChangedDelegate.AddDynamic(this, &UHudWidget::UpdateLifeDisplay);
			}
		}
	}
}

void UHudWidget::UpdateTimerDisplay(float Time)
{
	if (!TimerText) return;

	const int MinutesRemain = Time / 60.0f;
	const int SecondsRemain = Time - MinutesRemain * 60.0f;

	const FString TimeString = FString::Printf(TEXT("%02d:%02d"), MinutesRemain, SecondsRemain);
	TimerText->SetText(FText::FromString(TimeString));
}

void UHudWidget::UpdateScoreDisplay(int32 ScoreAmount)
{
	if (!ScoreText) return;

	const FString ScoreString = FString::Printf(TEXT("Score: %d"), ScoreAmount);
	ScoreText->SetText(FText::FromString(ScoreString));
}

void UHudWidget::UpdateLifeDisplay(int Life)
{
	// 현재는 이미지가 5개이므로 5개 이하로만 작동한다.
	Life = Life <= 5 ? Life : 5;
	
	TArray<UWidget*> Children;
	WidgetTree->GetChildWidgets(LifeContainer, Children);
	if (Children.Num() < 5)
	{
		return;
	}

	int ActivateWidget = 0;
	for (UWidget* Widget : Children)
	{
		if (ActivateWidget < Life)
		{
			Widget->SetVisibility(ESlateVisibility::Visible);
			ActivateWidget++;
		}
		else
		{
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}
