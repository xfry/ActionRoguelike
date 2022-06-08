// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "DrawDebugHelpers.h"
#include "DisplayDebugHelpers.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ObjMesh = CreateDefaultSubobject<UStaticMeshComponent>("BarrelMesh");
	RootComponent = ObjMesh;

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForceComp->SetupAttachment(ObjMesh);

    RadialForceComp->bImpulseVelChange = true;
    RadialForceComp->Radius = 2000.0f;
    RadialForceComp->ImpulseStrength = 1000.0f;
    RadialForceComp->DestructibleDamage = 500.0f;
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	ObjMesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	//This delegate should be bind inside BeginPlay method
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hitted"));
	RadialForceComp->FireImpulse();
	DrawDebugSphere(
		GetWorld(),
		otherActor->GetActorLocation(),
		50.0f,
		12,
		FColor::Green,
		false,
		3.0f,
		0,
		3.0f);
}
