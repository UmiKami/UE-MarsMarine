// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MM_MarsGameMode.h"

void AMM_MarsGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(GameStartDelayTimer, this, &ThisClass::SetupNewWave, StartDelay, false);
}

void AMM_MarsGameMode::SetupNewWave()
{
	
}

FString AMM_MarsGameMode::DisplayCurrentWave()
{
	FString DisplayMessage = FString::Printf(TEXT("Wave %d"), CurrentWave);
	
	return DisplayMessage;
}
