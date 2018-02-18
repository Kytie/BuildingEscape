// Copyright James Kyte 2018

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Grabber.generated.h"

USTRUCT()
struct FPlayerViewPoint
{
	GENERATED_BODY()

	UPROPERTY()
		FVector ViewLocation;

	UPROPERTY()
		FRotator ViewRotation;

	//Constructor
	FPlayerViewPoint()
	{
		ViewLocation = FVector(0.0f, 0.0f, 0.0f);
		ViewRotation = FRotator(0.0f, 0.0f, 0.0f);
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	UPROPERTY(EditAnywhere)
		float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	// Player viewpoint variable (UGrabber private member)
	FPlayerViewPoint PlayerViewPoint;

	bool RetrieveComponents();
	void BindInputs();
	void Grab();
	void Release();
	FHitResult GetFirstPhysicsBodyInReach();
	FVector GetReachLineEnd();
	void GetPlayerViewPoint();
};
