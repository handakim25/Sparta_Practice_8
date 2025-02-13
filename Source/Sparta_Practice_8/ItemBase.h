// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

UCLASS(Abstract)
class SPARTA_PRACTICE_8_API AItemBase : public AActor, public  IItemInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item")
	TObjectPtr<UStaticMeshComponent> Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Item", meta=(AllowPrivateAccess=true))
	TObjectPtr<UShapeComponent> Collision;
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void ActivateItem(AActor* Activator) override;
	virtual FName GetItemName() override;

	UFUNCTION()
	virtual void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void DestroyItem();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
