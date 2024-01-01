// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "ShooterCharacter.h"

// Sets default values
APickUpBase::APickUpBase() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComponent);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	rotationComponent = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("Rotation Component"));
	AddOwnedComponent(rotationComponent);
}

// Called when the game starts or when spawned
void APickUpBase::BeginPlay() {
	Super::BeginPlay();
	
	sphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUpBase::OnOverlapBegin);
	sphereComponent->OnComponentEndOverlap.AddDynamic(this, &APickUpBase::OnOverlapEnd);
}

// Called every frame
void APickUpBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APickUpBase::PickUp_Implementation(AActor* caller) {
	UE_LOG(LogTemp, Display, TEXT("Picked Up"));
}

bool APickUpBase::CanPickUp_Implementation(AActor* caller) {
	return true;
}

void APickUpBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (shooterCharacter && IPickUpInterface::Execute_CanPickUp(this, OtherActor))
		shooterCharacter->SetPickable(this, pickUpInfoText);
}

void APickUpBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(OtherActor);
	if (shooterCharacter)
		shooterCharacter->ClearPickable();
}

