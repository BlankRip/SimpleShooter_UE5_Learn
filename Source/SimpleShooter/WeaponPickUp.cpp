// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponPickUp.h"
#include "ShooterCharacter.h"

bool AWeaponPickUp::CanPickUp_Implementation(AActor* caller) {
	if (AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(caller)) {
		if (shooterCharacter->HasEmptyGunSlot())
			pickUpInfoText = "Press 'E' To Add Gun to Collection";
		else
			pickUpInfoText = "Press 'E' To Replace Gun";
	}
	return true;
}

void AWeaponPickUp::PickUp_Implementation(AActor* caller) {
	if (AShooterCharacter* shooterCharacter = Cast<AShooterCharacter>(caller)) {
		shooterCharacter->PickUpGun(gunClassToGive);
		Destroy();
	}
}
