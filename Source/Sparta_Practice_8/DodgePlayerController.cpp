// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HudWidget.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Blueprint/UserWidget.h"

ADodgePlayerController::ADodgePlayerController()
{
	// Top Down View이기 때문에 마우스 커서가 표기되어야 한다.
	bShowMouseCursor = true;

	ShortPressThreshold = 0.3f;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void ADodgePlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitUI();
}

void ADodgePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// 기본적인 이동은 디아블로 같은 느낌으로 이동하면 된다.
	// 누르고 있으면 해당 방향으로 이동하고
	// 빠르게 누르고 떼면 해당 위치로 이동
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// 처음 눌렀을 때 호출
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &ADodgePlayerController::OnClickStarted);
		// 누르고 있는 동안 호출
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &ADodgePlayerController::OnClickTriggered);
		// 트리거가 종료될 때 호출, 이 프레임에 None으로 전이된다.
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &ADodgePlayerController::OnClickCompleted);
		// 트리거가 Complete하기 전에 취소될 때 호출, Hold와 같은 동작일 경우에 발생한다.
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &ADodgePlayerController::OnClickCanceled);
	}
}

void ADodgePlayerController::OnClickStarted()
{
	StopMovement();
}

void ADodgePlayerController::OnClickTriggered()
{
	FollowTime += GetWorld()->GetDeltaSeconds();

	if (FHitResult Hit; GetHitResultUnderCursor(ECC_Visibility, true, Hit))
	{
		CachedDestination = Hit.Location;
		
	}
	
	if (APawn* ControlledPawn = GetPawn(); ControlledPawn != nullptr)
	{
		const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal2D();
		// Pawn에 이동 명령을 한다. Pawn은 자기 자신의 이동 컴포넌트를 이용해서 이동을 한다.
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void ADodgePlayerController::OnClickCompleted()
{
	if (FollowTime <= ShortPressThreshold)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}
	FollowTime = 0.f;
}

void ADodgePlayerController::OnClickCanceled()
{
	UE_LOG(LogTemp, Display, TEXT("OnClickCanceled"));
}

void ADodgePlayerController::InitUI()
{
	if (HudWidgetClass)
	{
		HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
		if (HudWidget)
		{
			HudWidget->AddToViewport();
		}
	}
}
