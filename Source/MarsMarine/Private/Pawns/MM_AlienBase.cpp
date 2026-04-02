// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/MM_AlienBase.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AMM_AlienBase::AMM_AlienBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMM_AlienBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMM_AlienBase::DamagePlayer()
{
		UGameplayStatics::ApplyDamage(
			UGameplayStatics::GetPlayerCharacter(this, 0),
			DamagePerHit,
			GetController(),
			this,
			nullptr
		);
}

// Called every frame
void AMM_AlienBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMM_AlienBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

