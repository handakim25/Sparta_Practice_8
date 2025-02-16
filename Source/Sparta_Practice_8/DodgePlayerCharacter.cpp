// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgePlayerCharacter.h"

#include "DodgeGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADodgePlayerCharacter::ADodgePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 캐릭터의 방향은 이동 방향으로만 결정된다.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	if (UCharacterMovementComponent* CharacterMovementComponent = GetCharacterMovement())
	{
		// 이동 방향으로 회전
		CharacterMovementComponent->bOrientRotationToMovement = true;
		CharacterMovementComponent->bConstrainToPlane = true;
		CharacterMovementComponent->bSnapToPlaneAtStart = true;
	}

	// 카메라를 고정된 위치에 두게 한다.
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1200.f;
	SpringArm->bDoCollisionTest = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

	MaxLife = 5;
	
	Tags.Add(FName("Player"));
}

// Called every frame
void ADodgePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADodgePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

int ADodgePlayerCharacter::GetLife() const
{
	return Life;
}

void ADodgePlayerCharacter::ModifyLife(int LifeAmount)
{
	Life += LifeAmount;
	Life = FMath::Clamp(Life, 0, MaxLife);

	OnLifeChangedDelegate.Broadcast(Life);
	
	if (Life <= 0)
	{
		// Death, 단순하게 GameOver를 호출. 체력 관리에 추가적인 기능이 있다면 HandlePlayerDeath 등으로 변경
		if (ADodgeGameModeBase* DodgeGameMode = GetWorld()->GetAuthGameMode<ADodgeGameModeBase>())
		{
			DodgeGameMode->GameOver(false);
		}
	}
}

void ADodgePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Life = MaxLife;
	OnLifeChangedDelegate.Broadcast(Life);
}

float ADodgePlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	ModifyLife(ActualDamage * -1);

	UE_LOG(LogTemp, Display, TEXT("Life: %d"), Life);
	
	return  ActualDamage;
}
