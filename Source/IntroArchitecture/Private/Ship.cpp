// Fill out your copyright notice in the Description page of Project Settings.


#include "Ship.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AShip::AShip()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShipMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	SetRootComponent(ShipMesh);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(ShipMesh);
	CameraBoom->TargetArmLength = 1000.0f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(CameraBoom);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AShip::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(ShipMappingContext, 0);
		}
	}
}

// Called every frame
void AShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(PropelUpAction, ETriggerEvent::Triggered, this, &AShip::PropelUp);
		EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &AShip::RotateShip);
	}
}

void AShip::PropelUp(const FInputActionValue& Value)
{
	if (bool CurrentValue = Value.Get<bool>())
	{
		const FVector WorldImpulseVector = FVector(0, 0, 1) * ImpulseStrength;
		const FVector LocalImpulse = GetActorRotation().RotateVector(WorldImpulseVector);
		ShipMesh->AddImpulse(LocalImpulse, NAME_None, true);
	}
}

void AShip::RotateShip(const FInputActionValue& Value)
{
	if (float CurrentValue = Value.Get<float>())
	{
		const FVector Torque = FVector(1, 0, 0) * (TorqueStrength * CurrentValue);
		ShipMesh->AddTorqueInRadians(Torque, NAME_None, true);
		UE_LOG(LogTemp, Warning, TEXT("Rotating ship with torque: %s"), *Torque.ToString());
	}
}

