// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sparta_Practice_8GameMode.h"
#include "Sparta_Practice_8PlayerController.h"
#include "Sparta_Practice_8Character.h"
#include "UObject/ConstructorHelpers.h"

ASparta_Practice_8GameMode::ASparta_Practice_8GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASparta_Practice_8PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}