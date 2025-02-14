// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

struct FItemSpawnData;

UCLASS()
class SPARTA_PRACTICE_8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnActorRandomLocationInVolume(UClass* SpawnActorClass) const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float SpawnHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int RandomSpawnTryCount = 3;
};
