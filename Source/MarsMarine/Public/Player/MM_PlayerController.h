// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MM_PlayerController.generated.h"

/**
 * 
 */

class UInputMappingContext;


UCLASS()
class MARSMARINE_API AMM_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMM_PlayerController() ;

protected:
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
};
