// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MM_MarsGameMode.h"

void AMM_MarsGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(GameStartDelayTimer, this, &ThisClass::StartNewWave, StartDelay, false);
}

void AMM_MarsGameMode::StartNewWave()
{
	FTimerManager& WorldTimerManager = GetWorldTimerManager();
	
	WorldTimerManager.ClearTimer(GameStartDelayTimer);
	
	IncreaseWaveDifficulty();
	
	CurrentWave++;
	
	WorldTimerManager.SetTimer(SpawnWaveTimer,this, &ThisClass::SpawnWaveTimerAction,1.f, true);
}

void AMM_MarsGameMode::EndWave()
{
	GetWorldTimerManager().SetTimer(SpawnWaveTimer, this, &ThisClass::StartNewWave, 2.f, false);
}

void AMM_MarsGameMode::TrySpawningNextWave()
{
	if (AlienSpawnsRemaining > 0 || RemainingAliens.Num() > 0) return;
	
	GetWorldTimerManager().ClearTimer(SpawnWaveTimer);
	
	EndWave();
}

void AMM_MarsGameMode::SpawnWaveTimerAction()
{
	if (AlienSpawnsRemaining > 0)
	{
		SpawnWaveSignature.Broadcast();
	} else
	{
		GetWorldTimerManager().ClearTimer(SpawnWaveTimer);
	}
}

void AMM_MarsGameMode::IncreaseWaveDifficulty()
{
	WaveDifficulty *= DifficultyMultiplier;
	AlienSpawnsRemaining = WaveDifficulty;
}

FString AMM_MarsGameMode::DisplayCurrentWave()
{
	FString DisplayMessage = FString::Printf(TEXT("Wave %d"), CurrentWave);
	
	return DisplayMessage;
}
