// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "DodgeGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int32, Score);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeChanged, float, RemainTime);

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API ADodgeGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ADodgeGameState();

	FOnScoreChanged OnScoreChangedDelegate;
	
	UFUNCTION(Blueprintpure, Category = "Score")
	int32 GetScore() const;

	// 점수를 변경한다.
	// 음수 점수는 지원하지 않는다.
	UFUNCTION(BlueprintCallable, Category = "Score")
	void ModifyScore(int32 ScoreAmount);

	FOnTimeChanged OnTimeChangedDelegate;

	UFUNCTION(BlueprintCallable, Category = "Time")
	void UpdateTime(float NewRemainTime);
	
	UFUNCTION(Blueprintpure, Category = "Time")
	float GetRemainTime() const;
	
private:
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleInstanceOnly, Transient, Category = "Time")
	float RemainTime;
};
