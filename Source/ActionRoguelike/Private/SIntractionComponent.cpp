// Fill out your copyright notice in the Description page of Project Settings.


#include "SIntractionComponent.h"

#include "SIInteractuable.h"

// Sets default values for this component's properties
USIntractionComponent::USIntractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USIntractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void USIntractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USIntractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);
	FHitResult HitResult;
	
	FVector EyeLocation;
	FRotator EyeRotation;

	AActor* myOwner = GetOwner();
	myOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector end = EyeLocation + (EyeRotation.Vector() * 1000);

	GetWorld()->LineTraceSingleByObjectType(HitResult, EyeLocation, end, ObjectQueryParams);
	AActor* HitActor = HitResult.GetActor();

	if(HitActor)
	{
		//Cast your HitActor to the interface: If it don't owns the interface then it will be NULL
		//ISIInteractuable* HitActorCast = Cast<ISIInteractuable>(HitActor); 
		if(HitActor->Implements<USIInteractuable>())
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("HitActor Cast Sucecssfull"));
			APawn* castedOwner = Cast<APawn>(myOwner);
			//HitActorCast->Execute_Interact(HitActor, castedOwner);
			ISIInteractuable::Execute_Interact(HitActor, castedOwner);
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("No Actor Found"));
	}
}