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
		FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);

		for (auto It : LevelTimerDataTable->GetRowMap())
		{
			const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
			if (Row && Row->LevelName == CurrentLevelName)
			{
				CountdownTimer = Row->TimerValue;
			}
		}
	}

	Timer = CountdownTimer;
}

void ALanderGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsTimerRunning)
	{
		Timer -= DeltaTime;

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

void ALanderGameMode::AddToTimer(float Value)
{
	UE_LOG(LogTemp, Warning, TEXT("Value Amount that is passed from the collectable: %f"), Value)
	UE_LOG(LogTemp, Warning, TEXT("Timer Value Before Addition: %f"), Timer);
	Timer = Timer + Value;
	UE_LOG(LogTemp, Warning, TEXT("TimerValue AfterAddition: %f"), Timer);
}

void ALanderGameMode::StopTimer()
{
	bIsTimerRunning = false;
}

void ALanderGameMode::LoadNextLevel()
{
	int32 CurrentLevelID = GetCurrentLevelID();
	if (CurrentLevelID != -1)
	{
		int32 NextLevelID = CurrentLevelID + 1;

		for (auto It : LevelTimerDataTable->GetRowMap())
		{
			const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
			if (Row && Row->LevelID == NextLevelID)
			{
				UGameplayStatics::OpenLevel(this, Row->LevelName);
				return;
			}
		}
	}
}

int32 ALanderGameMode::GetCurrentLevelID() const
{
	FName CurrentLevelName = *UGameplayStatics::GetCurrentLevelName(this);

	for (auto It : LevelTimerDataTable->GetRowMap())
	{
		const FLevelTimerData* Row = reinterpret_cast<const FLevelTimerData*>(It.Value);
		if (Row && Row->LevelName == CurrentLevelName)
		{
			return Row->LevelID;
		}
	}
	return -1;

}
