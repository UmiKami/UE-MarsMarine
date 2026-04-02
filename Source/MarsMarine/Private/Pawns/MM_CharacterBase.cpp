

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


	if (!NiagaraMuzzleFlash)
	{
		NiagaraMuzzleFlash = FindComponentByTag<UNiagaraComponent>("MuzzleFlash");
	}
}

void AMM_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::StartFiringWeapon);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ThisClass::StopFiringWeapon);
}

void AMM_CharacterBase::StartFiringWeapon(const FInputActionValue& Value)
{
	// VFX
	if (!NiagaraMuzzleFlash) return;
	NiagaraMuzzleFlash->Activate();
	
	// Sound
	if (!SpawnedRifleShotAudioComponent)
	{
		SpawnedRifleShotAudioComponent = UGameplayStatics::SpawnSound2D(this, RifleShotSound);
	}

	if (SpawnedRifleShotAudioComponent->IsPlaying()) { SpawnedRifleShotAudioComponent->Stop(); }

	SpawnedRifleShotAudioComponent->SetSound(RifleShotSound);
	SpawnedRifleShotAudioComponent->Play();
}

void AMM_CharacterBase::StopFiringWeapon(const FInputActionValue& Value)
{
	// VFX
	if (!NiagaraMuzzleFlash) return;

	NiagaraMuzzleFlash->Deactivate();

	// Sound
	if (!SpawnedRifleShotAudioComponent) return;
	
	SpawnedRifleShotAudioComponent->Stop();
	SpawnedRifleShotAudioComponent->SetSound(EndRifleShotSound);
	SpawnedRifleShotAudioComponent->Play();
}
