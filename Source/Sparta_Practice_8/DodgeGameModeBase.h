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
	
	UFUNCTION(BlueprintCallable)
	void NextLevel();
	UFUNCTION(BlueprintCallable)
	void GameOver();
	UFUNCTION(BlueprintCallable)
	void ModifyScore(int PointAmount);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Wave")
	TObjectPtr<UDataTable> WaveDataTable;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave")
	int CurrentWaveIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Wave")
	FName NextWaveMap;
	int WaveCount;
	
	void InitDataFromGameInstance();
	virtual void BeginPlay() override;

	virtual void OnLevelTimerUp();
	void OnUpdateTimer();

	/** 남은 시간을 반환한다.*/
	UFUNCTION(BlueprintPure)
	float GetRemainTime() const;
	
private:
	FTimerHandle LevelTimerHandle;
	FTimerHandle UpdateTimerHandle;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float LevelTimeLimit;
	UPROPERTY(EditInstanceOnly, meta=(AllowPrivateAccess=true))
	float TimerUpdateInterval;
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Level")
	int SpawnItemCount;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Level")
	int SpawnEnemyCount;
	
	void InitLevel();

};
