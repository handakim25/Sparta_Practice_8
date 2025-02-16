// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnVolume.h"
#include "WaveSpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API AWaveSpawnVolume : public ASpawnVolume
{
	GENERATED_BODY()
public:
	AWaveSpawnVolume();
	virtual  void BeginPlay() override;

	/** Wave Index에 맞추어서 스폰*/
	UFUNCTION(BlueprintCallable, Category="Wave")
	void SpawnWaves(int32 WaveIndex);

	UFUNCTION(BlueprintCallable, Category = "Wave")
	void DestroyAllSpawnedActors();

	/** Wave의 개수를 반환한다. WaveData의 설정, SpawnData 중에서 작은 값을 반환한다.*/
	UFUNCTION(BlueprintPure, Category = "Wave")
	int GetWaveCount() const;
	UFUNCTION(BlueprintPure, Category = "Wave")
	int GetWaveTimeLimit(int WaveIndex) const;
	UFUNCTION(BlueprintPure, Category = "Wave")
	bool IsValidWaveIndex(int WaveIndex) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TObjectPtr<UDataTable> WaveDataTable;
	TArray<struct FWaveData*> WaveData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TArray<UDataTable*> SpawnDataTables;
	TArray<TArray<FItemSpawnData*>> SpawnData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Wave")
	TSubclassOf<class AEnemyCharacter> EnemyClass;
	
	UPROPERTY(Transient)
	TArray<AActor*> SpawnedActors;

	UClass* GetRandomItemClass(int WaveIndex) const;
};
