// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeGameModeBase.h"

#include "DodgeGameInstance.h"
#include "DodgeGameState.h"
#include "DodgePlayerController.h"
#include "WaveSpawnVolume.h"
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

	WaveTimeLimit = 5.f;
	TimerUpdateInterval = 0.1f;
	WaveSpawnVolume = nullptr;
}

void ADodgeGameModeBase::NextLevel()
{
	ADodgeGameState* DodgeGameState = GetGameState<ADodgeGameState>();
	if (!DodgeGameState)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get game state"));
		return;
	}
	
	const float RemainTime = GetRemainTime();
	UDodgeGameInstance* GameInstance = GetGameInstance<UDodgeGameInstance>();
	if (!GameInstance)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get game instance"));
		return;
	}
	GameInstance->TotalScore += DodgeGameState->GetScore();
	GameInstance->TotalPlayTime += RemainTime;

	int NextWaveIndex = DodgeGameState->GetWaveIndex() + 1;
	int WaveCount = WaveSpawnVolume->GetWaveCount();
	if (NextWaveIndex >= WaveCount)
	{
		// Game Clear
		UE_LOG(LogTemp, Display, TEXT("Clear Game"));
		GameOver(true);
		return;
	}

	// Start Level
	StartWave(NextWaveIndex);
}

// 클리어 시에 true, 실패 시에 false
void ADodgeGameModeBase::GameOver(bool bIsClearGame)
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(UpdateTimerHandle);

	if (ADodgePlayerController* PlayerController = GetWorld() ? GetWorld()->GetFirstPlayerController<ADodgePlayerController>() : nullptr)
	{
		PlayerController->SetPause(true);
		PlayerController->StopMovement();
		PlayerController->ShowMainMenu(bIsClearGame);
	}
}

void ADodgeGameModeBase::ModifyScore(int PointAmount)
{
	if (ADodgeGameState* DodgeGameState = Cast<ADodgeGameState>(GameState))
	{
		DodgeGameState->ModifyScore(PointAmount);
	}
}

void ADodgeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	// Cache SpawnVolume
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWaveSpawnVolume::StaticClass(), FoundVolumes);
	if (FoundVolumes.Num() <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find spawn volume."));
		return;
	}
	WaveSpawnVolume = Cast<AWaveSpawnVolume>(FoundVolumes[0]);
	
	StartWave(0);
}

void ADodgeGameModeBase::OnLevelTimerUp()
{
	GameOver(false);
}

void ADodgeGameModeBase::OnUpdateTimer() const
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

void ADodgeGameModeBase::StartWave(int32 WaveIndex)
{
	if (ADodgeGameState* DodgeGameState = GetGameState<ADodgeGameState>())
	{
		DodgeGameState->SetWaveIndex(WaveIndex);
	}
	WaveTimeLimit = WaveSpawnVolume->GetWaveTimeLimit(WaveIndex);
	
	// 레벨 초기화
	WaveSpawnVolume->DestroyAllSpawnedActors();
	WaveSpawnVolume->SpawnWaves(WaveIndex);
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	AActor* PlayerStart = FindPlayerStart(PlayerController);
	if (PlayerController && PlayerStart)
	{
		PlayerController->GetPawn()->TeleportTo(PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation());
	}
	
	// 타이머 리셋
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ADodgeGameModeBase::OnLevelTimerUp,
		WaveTimeLimit,
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
	// 초기값 전파
	OnUpdateTimer();
}
