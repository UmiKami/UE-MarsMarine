// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MM_UserWidgetBase.generated.h"

class AMM_CharacterBase;
/**
 * 
 */
UCLASS()
class MARSMARINE_API UMM_UserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMarineCharacter(AMM_CharacterBase* MarineCharacter);
	
protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AMM_CharacterBase> Marine;
};
