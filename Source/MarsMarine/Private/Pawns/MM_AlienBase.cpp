// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MM_AlienBase.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMM_AlienBase::AMM_AlienBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMM_AlienBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMM_AlienBase::DamagePlayer()
{
		UGameplayStatics::ApplyDamage(
			UGameplayStatics::GetPlayerCharacter(this, 0),
			DamagePerHit,
			GetController(),
			this,
			nullptr
		);
}

float AMM_AlienBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - DamageAmount, 0, 100.f);
	
	if (Health == 0)
	{
		KillAI();
	}
	
	return DamageAmount;
}

void AMM_AlienBase::KillAI()
{
	IsDead = true;
	GetMovementComponent()->Deactivate();
	SetActorEnableCollision(false);
	AlienIsDeadSignature.Broadcast(true);
}
