// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"

// Sets default values
AGunBase::AGunBase() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(root);
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(root);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay() {
	Super::BeginPlay();
	
	inClip = magSize;
	availableAmmo = maxAmmo;
	currentModeName = modeName_A;
}

// Called every frame
void AGunBase::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AGunBase::PullTrigger(bool primary) {
	if (primary) {
		if (CanFire()) {
			if (inClip > 0) {
				if (fieringModeB)
					FireBulletModeB();
				else
					FireBulletModeA();
			} else
				Reload();
		}
	} else
		TriggerSecondaryProperty();
}

void AGunBase::SwitchFieringMode() {
	TriggerSecondaryProperty();
	fieringModeB = !fieringModeB;
	if (fieringModeB)
		currentModeName = modeName_B;
	else
		currentModeName = modeName_A;
}

void AGunBase::Reload() {
	if (inClip != magSize) {
		if (availableAmmo > 0) {
			TriggerSecondaryProperty();
			availableAmmo += inClip;
			if ((availableAmmo - magSize) >= 0) {
				availableAmmo -= magSize;
				inClip = magSize;
			} else {
				inClip = availableAmmo;
				availableAmmo = 0;
			}
			UE_LOG(LogTemp, Warning, TEXT("RELOADING"));
		} else
			UE_LOG(LogTemp, Warning, TEXT("No ammo left"));
	}
}

bool AGunBase::CanFire() {
	return true;
}

void AGunBase::FireBulletModeA() {
	inClip--;
	UE_LOG(LogTemp, Warning, TEXT("Shoot bullet Mode A"));
}

void AGunBase::TriggerBulletSecondaryModeA() {
	UE_LOG(LogTemp, Warning, TEXT("Bullet Secondary Trigged Mode A"));
}

void AGunBase::FireBulletModeB() {
	inClip--;
	UE_LOG(LogTemp, Warning, TEXT("Shoot bullet Mode B"));
}

void AGunBase::TriggerBulletSecondaryModeB() {
	UE_LOG(LogTemp, Warning, TEXT("Bullet Secondary Trigged Mode B"));
}

FString AGunBase::GetGunName() const {
	return gunName;
}

FString AGunBase::GetGunModeName() const {
	return currentModeName;
}

int AGunBase::GetAmmoInClip() const {
	return inClip;
}

int AGunBase::GetAvailableAmmo() const {
	return availableAmmo;
}

void AGunBase::TriggerSecondaryProperty() {
	if (fieringModeB)
		TriggerBulletSecondaryModeB();
	else
		TriggerBulletSecondaryModeA();
}

