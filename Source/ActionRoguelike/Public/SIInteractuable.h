// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SIInteractuable.generated.h"

// This class does not need to be modified.
class APawn;
UINTERFACE(MinimalAPI)
class USIInteractuable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROGUELIKE_API ISIInteractuable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/** Pawn responsible for damage and other gameplay events caused by this actor. */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="IMethods")
	void Interact(APawn* InstigatorPawn);
};
