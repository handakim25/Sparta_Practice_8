// Fill out your copyright notice in the Description page of Project Settings.


#include "HudWidget.h"

#include "DodgeGameState.h"
#include "Components/TextBlock.h"

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (const auto GameState = GetWorld()->GetGameState<ADodgeGameState>())
	{
		UpdateTimerDisplay(GameState->GetRemainTime());
		GameState->OnTimeChangedDelegate.AddDynamic(this, &UHudWidget::UpdateTimerDisplay);
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

