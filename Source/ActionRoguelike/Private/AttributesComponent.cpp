// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->SetHealth();
	// ...
}

bool UAttributesComponent::ApplyHealtChange(float change)
{
	HealthAttr += change;
	if(HealthAttr > -0.1)
		OnHealthChanged.Broadcast(nullptr, this, HealthAttr, change);

	UE_LOG(LogTemp, Warning, TEXT("HEALT Change is %f"), change);
	return true;
}

void UAttributesComponent::SetHealth()
{
	HealthAttr = 100;
	UE_LOG(LogTemp, Warning, TEXT("HEALT Change is %f"), HealthAttr);
}

void UAttributesComponent::GetHealth()
{
	UE_LOG(LogTemp, Warning, TEXT("Actual Health %f"), HealthAttr);
}