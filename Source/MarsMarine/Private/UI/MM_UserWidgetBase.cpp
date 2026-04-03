// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MM_UserWidgetBase.h"

void UMM_UserWidgetBase::SetMarineCharacter(AMM_CharacterBase* MarineCharacter)
{
	Marine = MarineCharacter;
}

void UMM_UserWidgetBase::SetMarsGameMode(AMM_MarsGameMode* MarsGameMode)
{
	this->MarsGameMode = MarsGameMode;
}
