// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"

#include "Ship.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class INTROARCHITECTURE_API AShip : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AShip();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NotifyHit(
		UPrimitiveComponent* MyComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit) 
		override;

	bool IsLandedSafely();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Movement")
	float ImpulseStrength = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Movement")
	float TorqueStrength = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Movement")
	float MaxLandingVelocity = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Graphics")
	UStaticMeshComponent* ShipMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputMappingContext* ShipMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* PropelUpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ship | Input")
	UInputAction* RotateAction;

	void PropelUp(const FInputActionValue& Value);
	void RotateShip(const FInputActionValue& Value);	
	void HandleShipLanding();

private:

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* MainCamera;

	float CurrentVelocity = 0.0f;
};
