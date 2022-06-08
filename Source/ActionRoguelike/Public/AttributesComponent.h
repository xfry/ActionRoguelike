// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChangeDelegate, AActor*, instigator, UAttributesComponent*, AttribComp, float, health, float, change);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API UAttributesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttributesComponent();
	bool ApplyHealtChange(float change);
	void SetHealth();
	void GetHealth();

	UPROPERTY(BlueprintAssignable, Category="Custom Events")
	FOnHealthChangeDelegate OnHealthChanged;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes", meta=(AllowPrivateAccess="true"))
	float HealthAttr;
};