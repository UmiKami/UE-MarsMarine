#include "Pawns/MM_CharacterBase.h"
#include "EnhancedInputComponent.h"
#include "KismetTraceUtils.h"
#include "NiagaraComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Interaction/MM_EnemyInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/MM_PlayerController.h"
#include "UI/MM_UserWidgetBase.h"

// Sets default values
AMM_CharacterBase::AMM_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMM_CharacterBase::SetupPlayerHUD()
{
	UUserWidget* PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
	UMM_UserWidgetBase* MarineUserWidgetHUD = Cast<UMM_UserWidgetBase>(PlayerHUD);
	
	MarineUserWidgetHUD->SetMarineCharacter(this);
	MarineUserWidgetHUD->AddToViewport();
}

void AMM_CharacterBase::WeaponTrace()
{
	USkeletalMeshComponent* Rifle = FindComponentByTag<USkeletalMeshComponent>( "rifle");
	
	if (!Rifle) return;
	
	FHitResult OutHit;
	
	FVector Start = Rifle->GetSocketLocation("MuzzleFlashSocket");
	FVector End = Start + GetActorForwardVector() * WeaponRange;
	
	FCollisionQueryParams Params = FCollisionQueryParams::DefaultQueryParam; 
	Params.AddIgnoredActor(this);
	
	UKismetSystemLibrary::LineTraceSingle(this, Start, End, UEngineTypes::ConvertToTraceType(ECC_Visibility), false, {this}, EDrawDebugTrace::ForDuration, OutHit, true, FColor::Red, FColor::Green, 5.f);

	AActor* DamagedActor = OutHit.GetActor();
	
	if (OutHit.bBlockingHit && DamagedActor->Implements<UMM_EnemyInterface>())
	{
		UGameplayStatics::ApplyDamage(DamagedActor, WeaponDamage, GetController(), this, {});
	}
}

void AMM_CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (!NiagaraMuzzleFlash)
	{
		NiagaraMuzzleFlash = FindComponentByTag<UNiagaraComponent>("MuzzleFlash");
	}
	
	SetupPlayerHUD();
}

void AMM_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardBackwardAction, ETriggerEvent::Triggered, this, &ThisClass::MoveForwardsBackwards);
		EnhancedInputComponent->BindAction(MoveLeftRightAction, ETriggerEvent::Triggered, this, &ThisClass::MoveLeftRight);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ThisClass::StartFiringWeapon);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &ThisClass::StopFiringWeapon);
	}
}

void AMM_CharacterBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	LookAtCursorPosition(DeltaSeconds);
}


void AMM_CharacterBase::MoveForwardsBackwards(const FInputActionValue& Value)
{
	const float ScaleValue = Value.Get<float>();

	AddMovementInput({1, 0, 0}, ScaleValue);
}

void AMM_CharacterBase::MoveLeftRight(const FInputActionValue& Value)
{
	const float ScaleValue = Value.Get<float>();

	AddMovementInput({0, 1, 0}, ScaleValue);
}

void AMM_CharacterBase::LookAtCursorPosition(float DeltaTime)
{
	if (IsDead) return;
	
	if (!MPlayerController)
	{
		MPlayerController = Cast<AMM_PlayerController>(GetController());
	};

	if (!MPlayerController) return;

	float PositionX = 0.f;
	float PositionY = 0.f;

	MPlayerController->GetMousePosition(PositionX, PositionY);

	FVector2D MousePosition = {PositionX, PositionY};

	FVector WorldPosition = {};
	FVector WorldDirection = {};

	UGameplayStatics::DeprojectScreenToWorld(MPlayerController, MousePosition, WorldPosition, WorldDirection);

	const FVector EndPoint = WorldPosition + WorldDirection * 2000;

	FHitResult OutHit;
	GetWorld()->LineTraceSingleByChannel(OutHit, WorldPosition, EndPoint, ECC_Visibility);

	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), OutHit.Location);

	FRotator LookAtAmount = UKismetMathLibrary::RInterpTo(
		MPlayerController->GetControlRotation(),
		LookAtRotation,
		DeltaTime,
		MouseSmoothingInterpSpeed
	);

	MPlayerController->SetControlRotation({0, LookAtAmount.Yaw, 0});
}

void AMM_CharacterBase::StartFiringWeapon(const FInputActionValue& Value)
{
	// VFX
	if (!NiagaraMuzzleFlash || IsDead) return;
	
	NiagaraMuzzleFlash->Activate();
	
	// Sound
	if (!SpawnedRifleShotAudioComponent)
	{
		SpawnedRifleShotAudioComponent = UGameplayStatics::SpawnSound2D(this, RifleShotSound);
	}

	if (SpawnedRifleShotAudioComponent->IsPlaying()) { SpawnedRifleShotAudioComponent->Stop(); }

	SpawnedRifleShotAudioComponent->SetSound(RifleShotSound);
	SpawnedRifleShotAudioComponent->Play();
	
	WeaponTrace();
}

void AMM_CharacterBase::StopFiringWeapon(const FInputActionValue& Value)
{
	// VFX
	if (!NiagaraMuzzleFlash) return;

	NiagaraMuzzleFlash->Deactivate();

	// Sound
	if (!SpawnedRifleShotAudioComponent) return;
	
	SpawnedRifleShotAudioComponent->Stop();
	
	if (IsDead) return; 
	
	SpawnedRifleShotAudioComponent->SetSound(EndRifleShotSound);
	SpawnedRifleShotAudioComponent->Play();
}

float AMM_CharacterBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - DamageAmount, 0, 100);
	
	if (Health == 0)
	{
		IsDead = true;
		StopFiringWeapon({});
		GetMovementComponent()->Deactivate();
	}
	
	return DamageAmount;
}
