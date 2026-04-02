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

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* FireAction;
	UPROPERTY(VisibleAnywhere, Category="VFX")
	TObjectPtr<UNiagaraComponent> NiagaraMuzzleFlash;
	
	UPROPERTY(EditDefaultsOnly, Category="SFX")
	TObjectPtr<USoundBase> RifleShotSound;
	
	UPROPERTY(EditDefaultsOnly, Category="SFX")
	TObjectPtr<USoundBase> EndRifleShotSound;
	UPROPERTY()
	TObjectPtr<UAudioComponent> SpawnedRifleShotAudioComponent;
	void StartFiringWeapon(const FInputActionValue& Value);
	void StopFiringWeapon(const FInputActionValue& Value);
};
