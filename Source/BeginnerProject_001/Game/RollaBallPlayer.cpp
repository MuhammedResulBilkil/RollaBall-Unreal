// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");

	RootComponent = StaticMeshComponent;
	SpringArmComponent->SetupAttachment(StaticMeshComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	StaticMeshComponent->SetSimulatePhysics(true);
	StaticMeshComponent->SetGenerateOverlapEvents(true);
	StaticMeshComponent->SetNotifyRigidBodyCollision(true);
	StaticMeshComponent->SetMassOverrideInKg(NAME_None, 1.0f, true);

	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->TargetArmLength = 1000.0f;
	SpringArmComponent->AddLocalRotation(FRotator(-40.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//StaticMeshComponent->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHit);
	
	/*MoveForce *= StaticMeshComponent->GetMass();
	JumpImpulse *= StaticMeshComponent->GetMass();*/
}

// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PlayerController = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ARollaBallPlayer::Move);
	EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ARollaBallPlayer::Jump);
}

void ARollaBallPlayer::Move(const FInputActionValue& ActionValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), TEXT(__FUNCTION__), *ActionValue.ToString(), ActionValue.GetMagnitude());

	const FVector Right = CameraComponent->GetRightVector() * MoveForce * ActionValue.Get<FVector2d>().Y;
	const FVector Forward = CameraComponent->GetForwardVector() * MoveForce * ActionValue.Get<FVector2d>().X;
	
	StaticMeshComponent->AddForce(Right + Forward);
}

void ARollaBallPlayer::Jump(const FInputActionValue& ActionValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("%s called with Input Action Value %s (magnitude %f)"), TEXT(__FUNCTION__), *ActionValue.ToString(), ActionValue.GetMagnitude());

	DrawDebugLine(GetWorld(), StaticMeshComponent->GetComponentLocation(),
			StaticMeshComponent->GetComponentLocation() - FVector(0, 0, 60), FColor::Blue, false, 5.0f, 0, 5.0f);
	
	if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(
		HitResult, StaticMeshComponent->GetComponentLocation(),
		StaticMeshComponent->GetComponentLocation() - FVector(0, 0, 60), ECC_Visibility))
	{
		//UE_LOG(LogTemp, Warning, TEXT("Ground!!!"));

		StaticMeshComponent->AddImpulse(FVector(0, 0, JumpImpulse));
	}
}

void ARollaBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, TEXT("Hit!"));
	
	//Log the hit
	UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitComponent->GetName());
}

