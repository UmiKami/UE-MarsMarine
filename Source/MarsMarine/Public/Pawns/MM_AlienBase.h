// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MM_AlienBase.generated.h"

UCLASS()
class MARSMARINE_API AMM_AlienBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMM_AlienBase();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DamagePlayer();
	
private:
	UPROPERTY(EditDefaultsOnly)
	float DamagePerHit = 5.f;
};
