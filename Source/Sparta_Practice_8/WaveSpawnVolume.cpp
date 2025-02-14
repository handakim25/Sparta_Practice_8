// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveSpawnVolume.h"

#include "ItemSpawnData.h"
#include "WaveData.h"

AWaveSpawnVolume::AWaveSpawnVolume()
{
}

// WaveDataTable, SpawnDataTables를 이용하여 WaveData, SpawnData를 캐싱
void AWaveSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	if (WaveDataTable)
	{
		WaveDataTable->GetAllRows<FWaveData>(TEXT("WaveContext"), WaveData);
	}

	// 캐싱에서 메모리 관련 이슈는 없을까?
	SpawnData.SetNum(SpawnDataTables.Num());
	for (int i = 0; i < SpawnDataTables.Num(); ++i)
	{
		if (SpawnDataTables[i])
		{
			SpawnDataTables[i]->GetAllRows<FItemSpawnData>(TEXT("ItemSpawnContext"), SpawnData[i]);

			float TotalChance = 0.f;
			for (const FItemSpawnData* Row : SpawnData[i])
			{
				if (Row)
				{
					TotalChance += Row->SpawnChance;
				}
			}
			WaveData[i]->TotalChance = TotalChance;
		}
	}
}

void AWaveSpawnVolume::SpawnWaves(int32 WaveIndex)
{
	if (!IsValidWaveIndex(WaveIndex))
	{
		UE_LOG(LogTemp,Warning,TEXT("Invalid Wave Index"));
		return;
	}

	int SpawnCount = WaveData[WaveIndex]->ItemSpawnCount;
	for (int i = 0; i < SpawnCount; ++i)
	{
		if (UClass* ActorClass = GetRandomItemClass(WaveIndex))
		{
			if (AActor* SpawnedActor = SpawnActorRandomLocationInVolume(ActorClass))
			{
				SpawnedActors.Add(SpawnedActor);
			}
		}
	}
}

void AWaveSpawnVolume::DestroyAllSpawnedActors()
{
	for (AActor* Actor : SpawnedActors)
	{
		if (Actor)
		{
			Actor->Destroy();
		}
	}

	SpawnedActors.Empty();
}

int AWaveSpawnVolume::GetWaveCount() const
{
	return FMath::Min(WaveData.Num(), SpawnDataTables.Num());
}

int AWaveSpawnVolume::GetWaveTimeLimit(int WaveIndex) const
{
	return IsValidWaveIndex(WaveIndex) ? WaveData[WaveIndex]->TimeLimit : 0;
}

bool AWaveSpawnVolume::IsValidWaveIndex(int WaveIndex) const
{
	return WaveIndex >= 0 && WaveIndex < WaveData.Num() && WaveIndex < SpawnDataTables.Num();
}

UClass* AWaveSpawnVolume::GetRandomItemClass(int WaveIndex) const
{
	if (!IsValidWaveIndex(WaveIndex))
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid Wave Index"));
		return nullptr;
	}

	const float RandValue = FMath::FRandRange(0.f, WaveData[WaveIndex]->TotalChance);
	float AccumulateChance = 0.f;
	for (const FItemSpawnData* Row : SpawnData[WaveIndex])
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue < AccumulateChance)
		{
			return Row->ActorClass.Get();
		}
	}

	return nullptr;
}
