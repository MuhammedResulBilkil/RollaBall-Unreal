// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RollaBallGameModeBase.generated.h"

class URollaBallWidget;

/**
 * 
 */
UCLASS()
class BEGINNERPROJECT_001_API ARollaBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	
	int32 CollectedItemCount = 0;
	int32 TotalItemCount = 0;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> GameWidgetClass;

	UPROPERTY()
	URollaBallWidget* GameWidget;

	virtual void BeginPlay() override;
	
	void UpdateItemText();

public:
	
	void ItemCollected();
};
