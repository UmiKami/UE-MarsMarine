// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interaction/MM_EnemyInterface.h"
#include "MM_AlienBase.generated.h"

class UWidgetComponent;
class AMM_AlienBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAlienDeathSignature, bool, IsDead, AMM_AlienBase*, AlienInstance);

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
	
	UFUNCTION(BlueprintImplementableEvent)
	void AlienHasBeenHurt();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> AlienHealthBarWidget;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsDead = false;
	
	UPROPERTY(BlueprintAssignable)
	FAlienDeathSignature AlienIsDeadSignature;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Health = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Diffculty Settings")
	TObjectPtr<UCurveTable> DifficultyCurve;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Diffculty Settings")
	float DamagePerHit = 5.f;
	
	float GetValueFromCurveTable(FName RowName, float Wave) const;
	
	void KillAI();
};
