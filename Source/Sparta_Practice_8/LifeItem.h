// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "LifeItem.generated.h"

/**
 * 
 */
UCLASS()
class SPARTA_PRACTICE_8_API ALifeItem : public AItemBase
{
	GENERATED_BODY()

public:
	ALifeItem();

protected:
	virtual void ActivateItem(AActor* Activator) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	int LifeAmount;
};
