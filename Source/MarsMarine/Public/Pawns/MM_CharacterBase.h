// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MM_CharacterBase.generated.h"

UCLASS()
class MARSMARINE_API AMM_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMM_CharacterBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
