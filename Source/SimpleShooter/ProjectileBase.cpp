// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	SetRootComponent(sphereComponent);
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(RootComponent);
	movementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	AddOwnedComponent(movementComponent);
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay() {
	Super::BeginPlay();
	
	movementComponent->bSweepCollision = true;
	sphereComponent->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHitComponent);
	sphereComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AProjectileBase::OnImpact(AActor* hitActor) {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, GetActorLocation());
}

void AProjectileBase::TriggerSecondaryAction_Implementation() {
}

void AProjectileBase::OnHitComponent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != GetOwner())
		OnImpact(OtherActor);
}
