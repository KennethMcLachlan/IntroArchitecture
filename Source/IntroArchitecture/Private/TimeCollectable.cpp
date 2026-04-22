// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeCollectable.h"
#include "Kismet/GameplayStatics.h"
#include "LanderGameMode.h"

// Sets default values
ATimeCollectable::ATimeCollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollectableMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectableMesh"));
	SetRootComponent(CollectableMesh);

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetupAttachment(CollectableMesh);
	SphereCollider->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATimeCollectable::OnOverlapBegin);

}

// Called when the game starts or when spawned
void ATimeCollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeCollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void ATimeCollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverlapTriggered!!"));
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (OtherActor && OtherActor == PlayerPawn)
	{
		SendCollectableValue();
		this->Destroy();
	}
}

void ATimeCollectable::SendCollectableValue()
{
	ALanderGameMode* GameMode = Cast<ALanderGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->AddToTimer(AddTimeValue);
	}
}

