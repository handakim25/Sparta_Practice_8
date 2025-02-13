// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DodgePlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API ADodgePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADodgePlayerController();

	// 이 시간 이하로 클릭할 경우 해당 위치로 이동을 실행한다.
	// 이 시간 이상으로 클릭할 경우 해당 방향으로 이동한다.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	float ShortPressThreshold;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Input")
	TObjectPtr<UInputAction> SetDestinationClickAction;
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	UFUNCTION()
	virtual void OnClickStarted();
	UFUNCTION()
	virtual void OnClickTriggered();
	UFUNCTION()
	virtual void OnClickCompleted();
	UFUNCTION()
	virtual void OnClickCanceled();

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Input")
	FVector CachedDestination;
	
	// 마우스 우클릭을 하고 있는 시간
	UPROPERTY(VisibleInstanceOnly, Category = "Input")
	float FollowTime;

protected:
	virtual void CreateHud();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UHudWidget> HudWidgetClass;
	UPROPERTY()
	TObjectPtr<class UHudWidget> HudWidget;
};
