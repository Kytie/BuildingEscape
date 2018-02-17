// Copyright James Kyte 2018

#include "PositionReport.h"
#include "GameFramework/Actor.h"



// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	// Dereferencing stuff as it converts FStrings to TCHAR array which is what UE_LOG wants to pass variables into string.
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *GetOwner()->GetName(), *GetOwner()->GetActorLocation().ToString());
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

