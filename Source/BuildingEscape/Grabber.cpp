// Copyright James Kyte 2018

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player viewpoint.
	FVector PlayerViewpointCurrLocation;
	FRotator PlayerViewpointCurrRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewpointCurrLocation, PlayerViewpointCurrRotation);
	FVector LineTraceEnd = PlayerViewpointCurrLocation + PlayerViewpointCurrRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewpointCurrLocation, LineTraceEnd, FColor(255,0,0,1), false, -1.0f, uint8('\000'), 5.0f);
	FHitResult LineTraceHit;
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		PlayerViewpointCurrLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(""), false, GetOwner())
	);

	if (IsValid(LineTraceHit.GetActor()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *LineTraceHit.GetActor()->GetName())
	}
}

