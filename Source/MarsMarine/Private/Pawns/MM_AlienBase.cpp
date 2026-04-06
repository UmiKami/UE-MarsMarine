// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MM_AlienBase.h"

#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"


AMM_AlienBase::AMM_AlienBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMM_AlienBase::BeginPlay()
{
	Super::BeginPlay();
	


	if (const AMM_MarsGameMode* MGameMode = Cast<AMM_MarsGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		const int32 CurrentWave = MGameMode->GetCurrentWave();
		
		GetCharacterMovement()->MaxWalkSpeed = GetValueFromCurveTable("Speed", CurrentWave);
		MaxHealth = GetValueFromCurveTable("MaxHealth", CurrentWave);
		
		Health = MaxHealth;
		
		DamagePerHit = GetValueFromCurveTable("DamagePerHit", CurrentWave);
	}


	AlienHasBeenHurt();
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

float AMM_AlienBase::GetValueFromCurveTable(FName RowName, float Wave) const
{
	if (DifficultyCurve)
	{
		if (const FRealCurve* Curve = DifficultyCurve->FindCurve(RowName, TEXT("Row could not be find for alien curve table.")))
		{
			return Curve->Eval(Wave);
		}
	}

	return 0.f;
}

void AMM_AlienBase::KillAI()
{
	IsDead = true;
	UPawnMovementComponent* MovementComponent = GetMovementComponent();
	
	MovementComponent->StopMovementImmediately();
	MovementComponent->Deactivate();
	
	SetActorEnableCollision(false);
	AlienIsDeadSignature.Broadcast(true, this);
}
