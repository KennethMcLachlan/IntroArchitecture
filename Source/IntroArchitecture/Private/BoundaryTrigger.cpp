// Fill out your copyright notice in the Description page of Project Settings.


#include "BoundaryTrigger.h"

// Sets default values for this component's properties
UBoundaryTrigger::UBoundaryTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoundaryTrigger::BeginPlay()
{
	Super::BeginPlay();

	AActor* ParentActor = GetOwner();
	if (ParentActor)
	{
		UBoxComponent* BoxComp = ParentActor->FindComponentByClass<UBoxComponent>();
		if (BoxComp)
		{
			BoxComp->OnComponentBeginOverlap.AddDynamic(this, &UBoundaryTrigger::OnOverlapBegin);
		}
	}
	
}


// Called every frame
void UBoundaryTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBoundaryTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetOwner())
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of bounds!"));
	}
}

