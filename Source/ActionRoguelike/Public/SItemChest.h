// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SIInteractuable.h"
#include "GameFramework/Actor.h"
#include "SItemChest.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ASItemChest : public AActor, public ISIInteractuable
{
	GENERATED_BODY()

	void Interact_Implementation(APawn *InstigatorPawn);

public:
	// Sets default values for this actor's properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Props")
	float targetPitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Props")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Props")
	UStaticMeshComponent* LidMesh;
	ASItemChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
