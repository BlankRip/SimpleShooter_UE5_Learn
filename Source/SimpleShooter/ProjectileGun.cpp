// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileGun.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectileBase.h"

void AProjectileGun::BeginPlay() {
	Super::BeginPlay();

	stickiesShot.Reserve(magSize);
}

AProjectileGun::AProjectileGun() {
	fieringPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Fiering Point"));
	fieringPoint->SetupAttachment(mesh);
}

void AProjectileGun::FireBulletModeA() {
	Super::FireBulletModeA();

	FireProjectile(simpleProjectileClass);
}

void AProjectileGun::FireBulletModeB() {
	Super::FireBulletModeB();

	stickiesShot.Add(FireProjectile(stickyProjectileClass));
}

void AProjectileGun::TriggerBulletSecondaryModeB() {
	for (AProjectileBase* porjectile : stickiesShot)
		porjectile->TriggerSecondaryAction();
	stickiesShot.Reset();
}

AProjectileBase* AProjectileGun::FireProjectile(TSubclassOf<AProjectileBase> projectileClass) {
	if (!projectileClass) {
		UE_LOG(LogTemp, Error, TEXT("One of the projectile classes is not assigned"));
		return nullptr;
	}

	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(muzzleSound, mesh, TEXT("MuzzleFlashSocket"));

	FHitResult hitResult;
	FVector shotDirection;
	FRotator roation = fieringPoint->GetComponentRotation();
	bool hitSomething = GunTrace(hitResult, shotDirection);
	if (hitSomething) {
		roation = (hitResult.Location - fieringPoint->GetComponentLocation()).Rotation();
	}

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this->GetOwner();
	AProjectileBase* spawned = GetWorld()->SpawnActor<AProjectileBase>(projectileClass,
		fieringPoint->GetComponentLocation(), roation, spawnParams);
	//spawned->SetUpOwner(this->GetOwner());

	return spawned;
}

bool AProjectileGun::GunTrace(FHitResult& hit, FVector& shotDirection) {
	FVector location;
	FRotator rotation;
	AController* ownerController = Cast<APawn>(GetOwner())->GetController();
	ownerController->GetPlayerViewPoint(location, rotation);
	shotDirection = -rotation.Vector();

	FVector end = location + rotation.Vector() * 5000.f;
	FCollisionQueryParams igonerParams;
	igonerParams.AddIgnoredActor(this);
	igonerParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, igonerParams);
}
