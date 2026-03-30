

#include "Pawns/MM_CharacterBase.h"

// Sets default values
AMM_CharacterBase::AMM_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMM_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMM_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMM_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

