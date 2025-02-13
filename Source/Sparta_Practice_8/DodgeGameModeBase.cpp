// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeGameModeBase.h"

#include "DodgeGameInstance.h"
#include "DodgeGameState.h"
#include "DodgePlayerController.h"
#include "SpawnVolume.h"
#include "WaveRow.h"
#include "Kismet/GameplayStatics.h"

ADodgeGameModeBase::ADodgeGameModeBase()
{
	GameStateClass = ADodgeGameState::StaticClass();
	static ConstructorHelpers::FClassFinder<AGameState> GameStateBPClass(TEXT("/Game/Blueprints/BP_DodgeGameState"));
	if (GameStateBPClass.Class != nullptr)
	{
		GameStateClass = GameStateBPClass.Class;
	}
	
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/BP_DodgePlayerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
		
	PlayerControllerClass = ADodgePlayerController::StaticClass();
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/BP_DodgePlayerController"));
	if (PlayerControllerBPClass.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	NextWaveMap = "";
	CurrentWaveIndex = 0;
	WaveCount = 0;
	LevelTimeLimit = 5.f;
	TimerUpdateInterval = 0.1f;
	SpawnItemCount = 0;
	SpawnEnemyCount = 0;
}

void ADodgeGameModeBase::NextLevel()
{
	const float RemainTime = GetRemainTime();
	
	UE_LOG(LogTemp, Display, TEXT("DodgeGameModeBase::NextLevel"));

	CurrentWaveIndex++;
	if (UDodgeGameInstance* GameInstance = GetGameInstance<UDodgeGameInstance>())
	{
		if (ADodgeGameState* DodgeGameState = GetGameState<ADodgeGameState>())
		{
			GameInstance->TotalScore += DodgeGameState->GetScore();
			GameInstance->TotalPlayTime += RemainTime;
			GameInstance->CurrentWaveIndex = CurrentWaveIndex;
		}
	}

	if (CurrentWaveIndex >= WaveCount)
	{
		// Game Clear
		UE_LOG(LogTemp, Display, TEXT("Clear Game"));
		GameOver();
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), NextWaveMap);
}

void ADodgeGameModeBase::GameOver()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(UpdateTimerHandle);

	if (ADodgePlayerController* PlayerController = GetWorld() ? GetWorld()->GetFirstPlayerController<ADodgePlayerController>() : nullptr)
	{
		PlayerController->SetPause(true);
		PlayerController->StopMovement();
	}
}

void ADodgeGameModeBase::ModifyScore(int PointAmount)
{
	if (ADodgeGameState* DodgeGameState = Cast<ADodgeGameState>(GameState))
	{
		DodgeGameState->ModifyScore(PointAmount);
	}
}

void ADodgeGameModeBase::InitDataFromGameInstance()
{
	UDodgeGameInstance* GameInstance = GetGameInstance<UDodgeGameInstance>();
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to access GameInstance, Check Game Instance setting"));
		return;
	}
	
	if (auto DodgeGameState = GetGameState<ADodgeGameState>())
	{
		DodgeGameState->SetScore(GameInstance->TotalScore);
	}
	
	CurrentWaveIndex = GameInstance->CurrentWaveIndex;
	if (!WaveDataTable)
	{
		UE_LOG(LogTemp, Error, TEXT("Empty Wave Data."));
		return;
	}

	TArray<FWaveRow*> AllRows;
	static const FString ContextString(TEXT("WaveContext"));
	WaveDataTable->GetAllRows(ContextString, AllRows);
	if (AllRows.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load wave data"));
		return;
	}

	WaveCount = AllRows.Num();
	
	if (CurrentWaveIndex + 1 < AllRows.Num())
	{
		FWaveRow* NextWaveRow = AllRows[CurrentWaveIndex + 1];
		NextWaveMap = NextWaveRow->MapName;
	}
	
	if (CurrentWaveIndex < AllRows.Num())
	{
		FWaveRow* WaveRow = AllRows[CurrentWaveIndex];
		LevelTimeLimit = WaveRow->TimeLimit;
		SpawnItemCount = WaveRow->ItemSpawnCount;
		SpawnEnemyCount = WaveRow->EnemySpawnCount;
	}
}

void ADodgeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Get Data from Game Instance
	InitDataFromGameInstance();
	
	// Timer
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ADodgeGameModeBase::OnLevelTimerUp,
		LevelTimeLimit,
		false
	);

	TimerUpdateInterval = FMath::Max(TimerUpdateInterval, 0.1f);
	GetWorldTimerManager().SetTimer(
		UpdateTimerHandle,
		this,
		&ADodgeGameModeBase::OnUpdateTimer,
		TimerUpdateInterval,
		true
	);

	// Get Data from Game Instance
	
	// 레벨을 Setup
	InitLevel();
}

void ADodgeGameModeBase::OnLevelTimerUp()
{
	GameOver();
}

void ADodgeGameModeBase::OnUpdateTimer()
{
	if (ADodgeGameState* DodgeGameState = GetGameState<ADodgeGameState>())
	{
		DodgeGameState->UpdateTime(GetRemainTime());
	}
}

float ADodgeGameModeBase::GetRemainTime() const
{
	return GetWorldTimerManager().IsTimerActive(LevelTimerHandle) ?
		GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle) : 0.0f;
}

void ADodgeGameModeBase::InitLevel()
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	if (FoundVolumes.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find spawn volume."));
		return;
	}
	ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
	if (!SpawnVolume)
	{
		return;
	}

	for (int i = 0; i < SpawnItemCount; i++)
	{
		SpawnVolume->SpawnRandomActorInVolume();
	}
}
