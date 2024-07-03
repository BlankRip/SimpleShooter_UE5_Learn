// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanGun.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Engine/DamageEvents.h"

void AHitScanGun::BeginPlay() {
	Super::BeginPlay();

	inBurst = false;
	amountShot = 0;
}

bool AHitScanGun::CanFire() {
	if (fieringModeB)
		return !inBurst;

	return true;
}

void AHitScanGun::FireBulletModeA() {
	Super::FireBulletModeA();

	FireRayTracedBullet();
}

void AHitScanGun::FireBulletModeB() {
	Super::FireBulletModeB();
	
	inBurst = true;
	FireRayTracedBullet();
	amountShot++;
	if (inClip > 0 && amountShot < bulletsInOneBurst)
		GetWorldTimerManager().SetTimer(burstTimer, this, &AHitScanGun::FireBulletModeB, gapBtwBullets, false);
	else {
		amountShot = 0;
		inBurst = false;
	}
}

void AHitScanGun::FireRayTracedBullet() {
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(muzzleSound, mesh, TEXT("MuzzleFlashSocket"));

	FHitResult hitResult;
	FVector shotDirection;
	bool hitSomething = GunTrace(hitResult, shotDirection);
	if (hitSomething) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitEffect, hitResult.Location, shotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), hitSound, hitResult.Location);

		FPointDamageEvent damageEvent(bulletDamage, hitResult, shotDirection, nullptr);
		if (hitResult.GetActor())
			hitResult.GetActor()->TakeDamage(bulletDamage, damageEvent, Cast<APawn>(GetOwner())->GetController(), this);
	}
}

bool AHitScanGun::GunTrace(FHitResult& hit, FVector& shotDirection) {
	FVector location;
	FRotator rotation;
	AController* ownerController = Cast<APawn>(GetOwner())->GetController();
	ownerController->GetPlayerViewPoint(location, rotation);
	shotDirection = -rotation.Vector();

	FVector end = location + rotation.Vector() * maxRange;
	FCollisionQueryParams igonerParams;
	igonerParams.AddIgnoredActor(this);
	igonerParams.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(hit, location, end, ECollisionChannel::ECC_GameTraceChannel1, igonerParams);
}
