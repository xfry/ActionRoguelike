// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceActor.h"
#include "SExplosiveBarrel.generated.h"

class URadialForceComponent;
UCLASS()
class ACTIONROGUELIKE_API ASExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASExplosiveBarrel();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

protected:
	// Called when the game starts or when spawned
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	UStaticMeshComponent* ObjMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Explosives", meta=(AllowPrivateAccess="true"))
	URadialForceComponent* RadialForceComp;

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
