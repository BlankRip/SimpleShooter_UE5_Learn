// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(muzzleSound, mesh, TEXT("MuzzleFlashSocket"));

	FHitResult hitResult;
	FVector shotDirection;
	bool hitSomething = GunTrace(hitResult, shotDirection);
	if (hitSomething) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, hitResult.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, hitResult.Location);

		FPointDamageEvent damageEvent(damage, hitResult, shotDirection, nullptr);
		if (hitResult.GetActor())
			hitResult.GetActor()->TakeDamage(damage, damageEvent, GetOwnerController(), this);
	}
}

bool AGun::GunTrace(FHitResult& hit, FVector& shotDirection) {
	FVector location;
	FRotator rotation;
	AController* ownerController = GetOwnerController();
	ownerController->GetPlayerViewPoint(location, rotation);
	shotDirection = -rotation.Vector();

	FVector end = location + rotation.Vector() * maxRange;
	FCollisionQueryParams igonerParams;
	igonerParams.AddIgnoredActor(this);
	igonerParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, igonerParams);
}

AController* AGun::GetOwnerController() const {
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	return ownerPawn->GetController();
}

