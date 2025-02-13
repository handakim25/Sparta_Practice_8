// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class SPARTA_PRACTICE_8_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

private:
	UPROPERTY(VisibleAnywhere, BlueprintreadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> SpawningBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	float SpawnHeightOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	int RandomSpawnTryCount = 3;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawning")
	TSubclassOf<AActor> SpawnActor;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Blueprintable, Category = "Spawning")
	FVector GetRandomPointInVolume() const;
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnActorInVolume(TSubclassOf<AActor> SpawnActorClass);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
