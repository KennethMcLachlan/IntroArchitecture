// Fill out your copyright notice in the Description page of Project Settings.


#include "LanderGameMode.h"

#include "Kismet/GameplayStatics.h"
#include <LevelEditorActions.h>

ALanderGameMode::ALanderGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	CountdownTimer = 30.0f;
}

void ALanderGameMode::BeginPlay()
{
	Super::BeginPlay();

	Timer = CountdownTimer;
}

void ALanderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Timer > 0)
	{
		Timer -= DeltaTime;
		UE_LOG(LogTemp, Warning, TEXT("Timer: %f"), CountdownTimer);

		if (Timer <= 0.0f)
		{
			FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this, true);
		    UGameplayStatics::OpenLevel(this, CurrentLevelName);
		}
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, INDEFINITELY_LOOPING_DURATION, FColor::Yellow, FString::Printf(TEXT("Timer: %f"), Timer));
	}
	
}
