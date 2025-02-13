// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeGameState.h"

ADodgeGameState::ADodgeGameState()
{
	Score = 0;
	RemainTime = 0.f;
}

int32 ADodgeGameState::GetScore() const
{
	return Score;
}

void ADodgeGameState::ModifyScore(int32 ScoreAmount)
{
	Score += ScoreAmount;
	Score = Score >= 0 ? Score : 0;

	OnScoreChangedDelegate.Broadcast(Score);
}

void ADodgeGameState::SetScore(int32 NewScore)
{
	Score = NewScore >= 0 ? NewScore : 0;

	OnScoreChangedDelegate.Broadcast(Score);
}

void ADodgeGameState::UpdateTime(float NewRemainTime)
{
	RemainTime = NewRemainTime >= 0.f ? NewRemainTime : 0.f;

	OnTimeChangedDelegate.Broadcast(NewRemainTime);
}

float ADodgeGameState::GetRemainTime() const
{
	return RemainTime;
}
