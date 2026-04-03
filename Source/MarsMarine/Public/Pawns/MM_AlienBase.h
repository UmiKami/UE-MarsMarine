// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/MM_EnemyInterface.h"
#include "MM_AlienBase.generated.h"

UCLASS()
class MARSMARINE_API AMM_AlienBase : public ACharacter, public IMM_EnemyInterface
{
	GENERATED_BODY()

public:
	AMM_AlienBase();


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DamagePlayer();
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float DamagePerHit = 5.f;
	
	UPROPERTY(EditDefaultsOnly)
	float Health = 100.f;
	
	// TODO: Consider adding MaxHealth to avoid hardcoding max value when clamping health.
};
