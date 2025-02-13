// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Components/ShapeComponent.h"

// Sets default values
AItemBase::AItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* RootScene = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(RootScene);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetupAttachment(RootScene);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (Collision)
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnItemOverlap);
	}
}

void AItemBase::ActivateItem(AActor* Activator)
{
}

FName AItemBase::GetItemName()
{
	return FName("Item");
}

void AItemBase::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ActivateItem(OtherActor);

		DestroyItem();
	}
}

void AItemBase::DestroyItem()
{
	Destroy();
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

