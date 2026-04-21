// Fill out your copyright notice in the Description page of Project Settings.


#include "LanderGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Data/LevelTimerData.h"
#include <LevelEditorActions.h>

ALanderGameMode::ALanderGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	//CountdownTimer = 30.0f;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableAsset(TEXT("/Script/Engine.DataTable'/Game/MyStuff/DataTables/LevelTimerData.LevelTimerData'"));

	if (DataTableAsset.Succeeded())
	{
		UE_LOG(LogTemp, Warning, TEXT("DT Found"));
		LevelTimerDataTable = DataTableAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Did NOT find DT"));
	}
}

void ALanderGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (LevelTimerDataTable != nullptr)
	{
		FName LevelName = *UGameplayStatics::GetCurrentLevelName(this, true);
		static const FString ContextString(TEXT("PrototypeLevel"));
		const FLevelTimerData* Row = LevelTimerDataTable->FindRow<FLevelTimerData>(LevelName, ContextString);

		if (Row != nullptr)
		{
			CountdownTimer = Row->TimerValue;
		}
	}

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
