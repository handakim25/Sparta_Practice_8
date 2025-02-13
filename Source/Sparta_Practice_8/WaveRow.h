// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaveRow.generated.h"

USTRUCT(BlueprintType)
struct SPARTA_PRACTICE_8_API FWaveRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName MapName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int TimeLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ItemSpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int EnemySpawnCount;
};
