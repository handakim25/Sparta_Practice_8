// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values
AEnemyController::AEnemyController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (AEnemyCharacter* EnemyCharacter = GetPawn<AEnemyCharacter>())
		{
			BlackboardComponent->SetValueAsFloat(TEXT("WaitTime"), EnemyCharacter->GetWaitTime());
		}
	}
	
	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
	}
}
