// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "ScoreItem.generated.h"

UCLASS()
class SPARTA_PRACTICE_8_API AScoreItem : public AItemBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScoreItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int PointAmount;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
