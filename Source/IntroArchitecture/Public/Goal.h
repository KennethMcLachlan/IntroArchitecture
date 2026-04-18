// Fill out your copyright notice in the Description page of Project Settings.


//TODO: Notify the goal that it has been hit (Physics Hit)
//TODO: by the ship actor
//TODO: Stop Timer?? We need a timer object
//TODO: Activate?? Celebration??

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

};
