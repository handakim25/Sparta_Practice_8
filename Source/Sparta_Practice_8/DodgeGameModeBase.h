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

	// Win / Lose
	UFUNCTION(BlueprintCallable)
	void NextLevel();
	UFUNCTION(BlueprintCallable)
	void GameOver(bool bIsClearGame);

	// Score
	UFUNCTION(BlueprintCallable)
	void ModifyScore(int PointAmount);
	
protected:
	virtual void BeginPlay() override;

	// Time
	virtual void OnLevelTimerUp();
	void OnUpdateTimer();

	/** 남은 시간을 반환한다.*/
	UFUNCTION(BlueprintPure)
	float GetRemainTime() const;
	
private:
	FTimerHandle LevelTimerHandle;
	FTimerHandle UpdateTimerHandle;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Transient, meta=(AllowPrivateAccess=true))
	float WaveTimeLimit;
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess=true))
	float TimerUpdateInterval;

protected:
	// Level
	UPROPERTY(Transient)
	class AWaveSpawnVolume* WaveSpawnVolume;

	virtual void StartWave(int32 WaveIndex);

};
