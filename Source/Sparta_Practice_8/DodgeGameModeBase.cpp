// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeGameModeBase.h"

#include "DodgeGameState.h"
#include "DodgePlayerController.h"

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

	LevelDuration = 5.f;
	TimerUpdateInterval = 0.1f;
}

void ADodgeGameModeBase::EndLevel(bool bIsGameWin)
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	GetWorldTimerManager().ClearTimer(UpdateTimerHandle);
	
	UE_LOG(LogTemp, Display, TEXT("DodgeGameModeBase::EndLevel"));
	// Pause Game
	// Show UI
	// Move to next level
}

void ADodgeGameModeBase::ModifyScore(int PointAmount)
{
	if (ADodgeGameState* DodgeGameState = Cast<ADodgeGameState>(GameState))
	{
		DodgeGameState->ModifyScore(PointAmount);
	}
}

void ADodgeGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UE_LOG(LogTemp, Display, TEXT("Init Game"));
}

void ADodgeGameModeBase::InitGameState()
{
	Super::InitGameState();

	UE_LOG(LogTemp, Display, TEXT("Init GameState"));
}

void ADodgeGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ADodgeGameModeBase::OnLevelTimerUp,
		LevelDuration,
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
}

void ADodgeGameModeBase::OnLevelTimerUp()
{
	EndLevel(false);
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
