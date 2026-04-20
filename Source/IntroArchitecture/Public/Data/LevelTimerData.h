#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "LevelTimerData.generated.h"

USTRUCT(BlueprintType)
struct FLevelTimerData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerValue;
};