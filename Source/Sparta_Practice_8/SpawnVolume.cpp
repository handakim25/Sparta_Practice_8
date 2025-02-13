// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "ActorSpawnRow.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* SceneRoot = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(SceneRoot);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>("SpawningBox");
	SpawningBox->SetupAttachment(SceneRoot);
	SpawningBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	SpawnHeightOffset = 64.f;
}

AActor* ASpawnVolume::SpawnRandomActorInVolume()
{
	if (FActorSpawnRow* SelectedRow = GetRandomSpawnRow())
	{
		if (UClass* ActualClass = SelectedRow->ActorClass.Get())
		{
			return SpawnActorRandomLocationInVolume(ActualClass);
		}
	}

	return nullptr;
}

void ASpawnVolume::SpawnFixedActorsInVolume()
{
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();

	int TryCount = RandomSpawnTryCount <= 0 ? 1 : RandomSpawnTryCount;
	while (TryCount--)
	{
		FVector StartLocation = BoxOrigin + FVector(
			FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
			FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
			BoxExtent.Z
		);

		FVector EndLocation = StartLocation + FVector::DownVector * BoxExtent.Z * 2;

		FHitResult Hit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, QueryParams))
		{
			return Hit.ImpactPoint + FVector::UpVector * SpawnHeightOffset;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Spawning Volume Failed"));
	return BoxOrigin;
}

AActor* ASpawnVolume::SpawnActorRandomLocationInVolume(TSubclassOf<AActor> SpawnActorClass)
{
	if (!SpawnActorClass) return nullptr;

	return GetWorld()->SpawnActor<AActor>(
		SpawnActorClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator
	);
}

FActorSpawnRow* ASpawnVolume::GetRandomSpawnRow() const
{
	if (!SpawnDataTable) return nullptr;

	TArray<FActorSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	SpawnDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return  nullptr;

	float TotalChance = 0.f;
	for (const FActorSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.f, TotalChance);
	float AccumulateChance = 0.f;
	for (FActorSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue < AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

