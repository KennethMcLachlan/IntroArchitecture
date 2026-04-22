// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Goal.generated.h"

UCLASS()
class INTROARCHITECTURE_API AGoal : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:	

	// Sets default values for this actor's properties
	AGoal();

	UPROPERTY(EditAnywhere, Category = "FX")
	UNiagaraSystem* CelebrationEffect;

	virtual void Tick(float DeltaTime) override;

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

	void HandleGoalReached();	

private:

	bool bIsGoalReached = false;
	bool bWaitingForParticleFX = false;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* CelebrationEffectComponent;

};
