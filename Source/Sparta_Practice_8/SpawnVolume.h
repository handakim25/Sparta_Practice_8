// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

struct FActorSpawnRow;

UCLASS()
class SPARTA_PRACTICE_8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UFUNCTION(BlueprintCallable)
	AActor* SpawnRandomActorInVolume();
	UFUNCTION(BlueprintCallable)
	void SpawnFixedActorsInVolume();
	
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume() const;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float SpawnHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int RandomSpawnTryCount = 3;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TObjectPtr<UDataTable> SpawnDataTable;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnActorRandomLocationInVolume(TSubclassOf<AActor> SpawnActorClass);
	FActorSpawnRow* GetRandomSpawnRow() const;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
