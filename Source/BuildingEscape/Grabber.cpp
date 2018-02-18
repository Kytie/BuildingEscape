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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	if (RetrieveComponents())
	{
		BindInputs();
	}
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

bool UGrabber::RetrieveComponents()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Physics Handle in %s not found!"), *GetOwner()->GetName())
		return 0;
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Input Component in %s not found!"), *GetOwner()->GetName())
		return 0;
	}
	return 1;
}

void UGrabber::BindInputs()
{
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Pressed event triggered!"))
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentHit = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *ActorHit->GetName())
		PhysicsHandle->GrabComponentAtLocation(ComponentHit, NAME_None, ActorHit->GetActorLocation());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release event triggered!"))
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult LineTraceHit;
	GetPlayerViewPoint();
	GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		PlayerViewPoint.ViewLocation,
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		FCollisionQueryParams(FName(""), false, GetOwner())
	);
	return LineTraceHit;
}

FVector UGrabber::GetReachLineEnd()
{
	GetPlayerViewPoint();
	return PlayerViewPoint.ViewLocation + PlayerViewPoint.ViewRotation.Vector() * Reach;
}

// Takes a reference to a FPlayerViewPoint reference
void UGrabber::GetPlayerViewPoint()
{
	// Using class member varible.
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPoint.ViewLocation, PlayerViewPoint.ViewRotation);
}
