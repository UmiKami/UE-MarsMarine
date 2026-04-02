// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MM_CharacterBase.generated.h"

struct FInputActionValue;
class UInputAction;
class AMM_PlayerController;
class UNiagaraComponent;

UCLASS()
class MARSMARINE_API AMM_CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AMM_CharacterBase();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetHealth() const {return Health;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE int32 GetEnemiesKilledCount() const {return EnemiesKilled;}

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveForwardBackwardAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveLeftRightAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* FireAction;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	float MouseSmoothingInterpSpeed = 1.f;
	
	UPROPERTY(VisibleAnywhere, Category="VFX")
	TObjectPtr<UNiagaraComponent> NiagaraMuzzleFlash;
	
	UPROPERTY(EditDefaultsOnly, Category="SFX")
	TObjectPtr<USoundBase> RifleShotSound;
	
	UPROPERTY(EditDefaultsOnly, Category="SFX")
	TObjectPtr<USoundBase> EndRifleShotSound;
	
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> PlayerHUDClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float Health;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	int32 EnemiesKilled;
	
private:
	UPROPERTY()
	TObjectPtr<AMM_PlayerController> MPlayerController;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> SpawnedRifleShotAudioComponent;
	
	void MoveForwardsBackwards(const FInputActionValue& Value);
	void MoveLeftRight(const FInputActionValue& Value);
	void LookAtCursorPosition(float DeltaTime);
	void StartFiringWeapon(const FInputActionValue& Value);
	void StopFiringWeapon(const FInputActionValue& Value);
	
	void SetupPlayerHUD();
};
