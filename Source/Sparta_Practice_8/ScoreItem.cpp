// Fill out your copyright notice in the Description page of Project Settings.


#include "ScoreItem.h"

#include "DodgeGameModeBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AScoreItem::AScoreItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collision = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AScoreItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AScoreItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (ADodgeGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ADodgeGameModeBase>())
	{
		GameMode->ModifyScore(PointAmount);
	}
}

// Called every frame
void AScoreItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

