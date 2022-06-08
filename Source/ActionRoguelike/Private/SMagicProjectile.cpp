// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "AttributesComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

class UParticleSystemComponent;
class UAttributesComponent;

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;
    SphereComp->SetCollisionProfileName("Projectile");
    //Set collision setting
    /*SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);*/

    EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
    EffectComp->SetupAttachment(SphereComp);

    MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMComp");
	MovementComp->InitialSpeed = 3000.0f;
	MovementComp->MaxSpeed = 8000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	AttributeComp = CreateDefaultSubobject<UAttributesComponent>("AttributeComponent");
}

// Called when the game starts or when spawned
void ASMagicProjectile::BeginPlay()
{
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OverlapResponse);
	Super::BeginPlay();
}

// Called every frame
void ASMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASMagicProjectile::OverlapResponse(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ensureMsgf(OtherActor, TEXT("There is not other actor")))
	{
		UAttributesComponent *OtherAttrComp = Cast<UAttributesComponent>(OtherActor->GetComponentByClass(UAttributesComponent::StaticClass()));
		if(OtherAttrComp)
		{
			OtherAttrComp->ApplyHealtChange(-20.0);
			OtherAttrComp->GetHealth();
		}

		Destroy();
	}
}