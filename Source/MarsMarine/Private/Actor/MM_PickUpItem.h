// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MM_PickUpItem.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class MARSMARINE_API AMM_PickUpItem : public AActor
{
	GENERATED_BODY()

public:
	AMM_PickUpItem();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UNiagaraComponent* ItemParticle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USphereComponent* SphereCollision;
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
