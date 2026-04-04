// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MM_MarsGameMode.generated.h"

class AMM_AlienBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAlienSpawnWaveSignature);

/**
 * 
 */
UCLASS()
class MARSMARINE_API AMM_MarsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FString DisplayCurrentWave();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void StartNewWave();
	
	void EndWave();
	
	UFUNCTION(BlueprintCallable)
	void TrySpawningNextWave();
	
	UFUNCTION()
	void SpawnWaveTimerAction();
	
	UFUNCTION()
	void IncreaseWaveDifficulty();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 WaveDifficulty = 5;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DifficultyMultiplier = 1.2f;
	
	UPROPERTY(BlueprintAssignable)
	FAlienSpawnWaveSignature SpawnWaveSignature;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AMM_AlienBase>> RemainingAliens;
	
	UPROPERTY(BlueprintReadWrite)
	int32 AlienSpawnsRemaining = 10;
	
	UPROPERTY(EditDefaultsOnly)
	float StartDelay = 2.f;
	
	int32 CurrentWave = 0;
	
	FTimerHandle GameStartDelayTimer;
	FTimerHandle SpawnWaveTimer;
};
