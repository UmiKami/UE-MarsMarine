// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_PickUpItem.h"

#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"


AMM_PickUpItem::AMM_PickUpItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ItemParticle = CreateDefaultSubobject<UNiagaraComponent>("ItemParticle");
	
	SetRootComponent(ItemParticle);
	
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	
	SphereCollision->SetupAttachment(RootComponent);
}

void AMM_PickUpItem::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlap);
}
