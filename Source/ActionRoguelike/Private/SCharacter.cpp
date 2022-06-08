// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DisplayDebugHelpers.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "SMagicProjectile.h"
#include "Containers/Union.h"

#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//instantiate components
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
    SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->bUsePawnControlRotation = true; //it works for camera

	CameraComp = CreateDefaultSubobject<UCameraComponent>("Camera");
    CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USIntractionComponent>("InteractComponent");
	AttributeComp = CreateDefaultSubobject<UAttributesComponent>("AttributeComponent");
	
	bUseControllerRotationYaw = false; //disable player rotation based on controller input
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASCharacter::MoveForward(float axis)
{
	FRotator ControlRotr = Controller->GetControlRotation();
	ControlRotr.Pitch = 0.0f;
	ControlRotr.Roll = 0.0f;
	
	AddMovementInput(ControlRotr.Vector(), axis);
}

void ASCharacter::MoveSides(float axis)
{
	//move without turning character
	//AddMovementInput(FVector(0, axis, 0));
	//AddMovementInput(GetActorRightVector(), axis);
	//move to sides but not rotate
	FRotator ControlRot = Controller->GetControlRotation();
	FVector Vright = FRotationMatrix::MakeFromX(ControlRot.Vector()).GetScaledAxis(EAxis::Y); //it return right vector EAxis::Y
	//FVector Vright = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y); //short way to do it.
	AddMovementInput(Vright, axis);
}

void ASCharacter::PrimaryAttack()
{
	//Animation Montage
	PlayAnimMontage(AttackAnim);

	//Set delay to animation and clean timer
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ASCharacter::PrimaryAttack_Anim, 0.2f);
	//GetWorld()->GetTimerManager().ClearTimer(TimerHandle_PrimaryAttack);
}

void ASCharacter::PrimaryAttack_Anim()
{
	if(ensureMsgf(ProjectileClass, TEXT("The Projectile Class has not been defined or imported")))
	{
		//Transform parameters
		FVector		const TLocation	= GetMesh()->GetSocketLocation("Muzzle_01");
		FRotator	LookAtRot = UKismetMathLibrary::FindLookAtRotation(TLocation, ProjectileDirection);

		//Spawning Parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; //actor can spawn projectile even when the projectile collide with its owner
		SpawnParams.Instigator = this;

		/*DrawDebugSphere(
			GetWorld(),
			GetActorLocation(),
			50.0f,
			12,
			FColor::Red,
			false,
			3.0f,
			0,
			3.0f);*/
		
		//spawn projectile	
		GetWorld()->SpawnActor<AActor>(ProjectileClass, TLocation, LookAtRot, SpawnParams);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Firing"));
	}
}

void ASCharacter::PrimaryInteract()
{
	if(InteractionComp)
		InteractionComp->PrimaryInteract();
}

void ASCharacter::SetProjectileDirection()
{
	//Line Trace from Camera to Object and set Object Position as Projectile Spawn Position.
	//FVector Start = GetMesh()->GetSocketLocation("Muzzle_01");
	FVector Start =  CameraComp->GetComponentLocation();
	FRotator Rotor = CameraComp->GetComponentRotation();
	FHitResult HitResult;
	FVector End = (Rotor.Vector() * 10000) + Start;
	FCollisionQueryParams TraceParams;
	
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);
	ProjectileDirection = HitResult.ImpactPoint;
	if(ProjectileDirection == FVector::ZeroVector)
		ProjectileDirection = HitResult.TraceEnd;

	//UE_LOG(LogTemp, Warning, TEXT("Impact Point: %s"), *ProjectileDirection.ToString());

	//DrawDebugDirectionalArrow(GetWorld(), Start, End, 200.0f, FColor::Red, false, 0.0f, 0, 4);
}


// Called every frame
void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Some variables we need for draw debug line
	const float DrawScale = 100.0f;
	const float Thickness = 5.0f;

	FVector ActorLineStart = GetActorLocation();
	ActorLineStart += GetActorRightVector() + 60.0f; //move line to the side of character
	const FVector ActorLineEnd = ActorLineStart + (GetActorForwardVector() * 60.0f);

	//call method for draw debug line
	DrawDebugDirectionalArrow(GetWorld(), ActorLineStart, ActorLineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0, Thickness);
	SetProjectileDirection();
	FVector MouseLineEnd = ActorLineStart + (GetControlRotation().Vector() * 60.0f);
	DrawDebugDirectionalArrow(GetWorld(), ActorLineStart, MouseLineEnd, DrawScale, FColor::Green, false, 0.0f, 0, Thickness);
		
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &ASCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ASCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASCharacter::MoveSides);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ASCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ASCharacter::PrimaryInteract);
}