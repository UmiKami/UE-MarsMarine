// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MM_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"


AMM_PlayerController::AMM_PlayerController()
{
	bShowMouseCursor = true;
}

void AMM_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
