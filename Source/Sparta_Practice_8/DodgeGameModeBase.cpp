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
}
