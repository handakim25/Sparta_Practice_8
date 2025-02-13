// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DodgeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API ADodgeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ADodgeGameModeBase();

	void EndLevel(bool bIsGameWin);
	void ModifyScore(int PointAmount);
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void InitGameState() override;
	virtual void BeginPlay() override;

	virtual void OnLevelTimerUp();
	void OnUpdateTimer();

	/** 남은 시간을 반환한다.*/
	UFUNCTION(BlueprintPure)
	float GetRemainTime() const;
private:
	FTimerHandle LevelTimerHandle;
	FTimerHandle UpdateTimerHandle;
	
	UPROPERTY(EditAnywhere)
	float LevelDuration;
	float TimerUpdateInterval;
};
