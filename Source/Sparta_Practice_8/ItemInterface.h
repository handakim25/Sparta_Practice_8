// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SPARTA_PRACTICE_8_API IItemInterface
{
	GENERATED_BODY()

	virtual void ActivateItem(AActor* Activator) = 0;
	virtual FName GetItemName() = 0;
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
