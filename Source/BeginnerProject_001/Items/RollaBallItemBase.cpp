// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallItemBase.h"

#include "BeginnerProject_001/Game/RollaBallGameModeBase.h"
#include "BeginnerProject_001/Game/RollaBallPlayer.h"

// Sets default values
ARollaBallItemBase::ARollaBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");

	RootComponent = StaticMeshComponent;
}

// Called when the game starts or when spawned
void ARollaBallItemBase::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ARollaBallItemBase::OverlapBegin);
}

void ARollaBallItemBase::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollaBallPlayer>(OtherActor))
	{
		Collected();
	}
}

void ARollaBallItemBase::Collected_Implementation()
{
	ARollaBallGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ARollaBallGameModeBase>();

	if (GameMode)
	{
		GameMode->ItemCollected();
	}
}

