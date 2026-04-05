// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MM_CharacterBase.generated.h"

class UNiagaraSystem;
struct FInputActionValue;
class UInputAction;
class AMM_PlayerController;
class UNiagaraComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayerDeathSignature, bool, IsDead);

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
	
	UFUNCTION(BlueprintCallable)
	void AddHealth(float InHealth);
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsPlayerHealthFull() const {return Health == MaxHealth;}
	

protected:
	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAlive() const {return !IsDead;}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void IncrementEnemyKillCount() {EnemiesKilled++;}
	
	UPROPERTY(BlueprintReadWrite)
	bool bOutsideMissionArea = false;
	
	UPROPERTY(EditDefaultsOnly)
	UNiagaraSystem* ImpactEffect;
	
	UPROPERTY(BlueprintReadWrite, Category="Player Status")
	bool IsDead = false;
	
	UPROPERTY(BlueprintAssignable, Category="Player Status")
	FPlayerDeathSignature PlayerDiedSignature;
	
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
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	int32 EnemiesKilled;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float WeaponRange = 5000.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float WeaponDamage = 25.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Player Stats")
	float WeaponFireRate = 0.08f;


private:
	FTimerHandle WeaponTraceFireRateTimer;
	
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
	void SetInitialStats();
	
	UFUNCTION(BlueprintCallable)
	void WeaponTrace();
};
