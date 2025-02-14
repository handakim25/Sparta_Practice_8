// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "EnemyController.generated.h"

UCLASS()
class SPARTA_PRACTICE_8_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBlackboardData> BlackboardData;
};
