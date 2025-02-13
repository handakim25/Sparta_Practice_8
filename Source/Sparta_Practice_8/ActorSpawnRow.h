// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct SPARTA_PRACTICE_8_API FActorSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ActorName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ActorClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int SpawnCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
};
