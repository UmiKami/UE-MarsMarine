// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MM_MarsGameMode.generated.h"

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
	void SetupNewWave();
	
	UPROPERTY(EditDefaultsOnly)
	float StartDelay = 2.f;
	
	int32 CurrentWave = 1;
	
	FTimerHandle GameStartDelayTimer;
};
