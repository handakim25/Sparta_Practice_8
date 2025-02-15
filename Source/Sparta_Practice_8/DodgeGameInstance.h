// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DodgeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API UDodgeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="GameData")
	float TotalPlayTime;

	UFUNCTION(BlueprintCallable)
	void ResetGame();
};
