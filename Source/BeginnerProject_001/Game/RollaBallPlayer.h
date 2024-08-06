// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "RollaBallPlayer.generated.h"

class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

struct FInputActionValue;

UCLASS()
class BEGINNERPROJECT_001_API ARollaBallPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ARollaBallPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Define Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input Actions")
	UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Input Mapping Contexts")
	UInputMappingContext* InputMapping;

	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MoveForce = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpImpulse = 500.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	int32 MaxJumpCount = 1;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:
	
	//Functions
	void Move(const FInputActionValue& ActionValue);
	void Jump(const FInputActionValue& ActionValue);

	UFUNCTION(Blueprintable, Category = "Collision")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
