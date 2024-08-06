// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallGameModeBase.h"

#include "RollaBallWidget.h"
#include "BeginnerProject_001/Items/RollaBallItemBase.h"
#include "Kismet/GameplayStatics.h"

void ARollaBallGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	TArray<AActor*> Items;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARollaBallItemBase::StaticClass(), Items);
	TotalItemCount = Items.Num();

	if(GameWidgetClass)
	{
		GameWidget = Cast<URollaBallWidget>(CreateWidget(GetWorld(), GameWidgetClass));

		if(GameWidget)
		{
			GameWidget->AddToViewport();
			UpdateItemText();
		}
	}
}

void ARollaBallGameModeBase::UpdateItemText()
{
	GameWidget->SetItemText(CollectedItemCount, TotalItemCount);
}

void ARollaBallGameModeBase::ItemCollected()
{
	CollectedItemCount++;
	UpdateItemText();
}
