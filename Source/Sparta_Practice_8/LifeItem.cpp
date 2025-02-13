// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeItem.h"

#include "DodgePlayerCharacter.h"
#include "Components/SphereComponent.h"

ALifeItem::ALifeItem()
{
	LifeAmount = 1;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Collision->SetCollisionProfileName(FName("OverlapAllDynamic"));
	Collision->SetupAttachment(RootComponent);
}

void ALifeItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (ADodgePlayerCharacter* Character = Cast<ADodgePlayerCharacter>(Activator))
	{
		Character->ModifyLife(LifeAmount);
	}
}
