// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributesComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SIntractionComponent.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;
class UAttributesComponent;

UCLASS()
class ACTIONROGUELIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Props", meta=(AllowPrivateAccess="true"))
	TSubclassOf<AActor> ProjectileClass;

	// Called when the game starts or when spawned
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USIntractionComponent* InteractionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animations")
	UAnimMontage* AttackAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAttributesComponent* AttributeComp;

	FTimerHandle TimerHandle_PrimaryAttack;

	FVector ProjectileDirection;
	
	virtual void BeginPlay() override;
	void MoveForward(float axis);
	void MoveSides(float axis);
	void PrimaryAttack();
	void PrimaryAttack_Anim();
	void PrimaryInteract();
	void SetProjectileDirection();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
