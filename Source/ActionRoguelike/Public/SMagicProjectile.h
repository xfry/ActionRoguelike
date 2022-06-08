// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "SMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAttributesComponent;
class UParticleSystem;

UCLASS()
class ACTIONROGUELIKE_API ASMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASMagicProjectile();

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Comps", meta=(AllowPrivateAccess="true"))
	USphereComponent *SphereComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Comps", meta=(AllowPrivateAccess="true"))
	UProjectileMovementComponent  *MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAttributesComponent* AttributeComp;

	UFUNCTION(BlueprintCallable, Category="Callbacks", meta=(AllowPrivateAccess="true"))
	void OverlapResponse(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
