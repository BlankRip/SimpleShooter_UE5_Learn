// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "HitScanGun.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AHitScanGun : public AGunBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	virtual bool CanFire() override;
	virtual void FireBulletModeA() override;
	virtual void FireBulletModeB() override;

private:
	void FireRayTracedBullet();
	bool GunTrace(FHitResult& hit, FVector& shotDirection);

	UPROPERTY(EditAnywhere, Category = "Mode Common Settings")
		float maxRange = 1000.f;
	UPROPERTY(EditAnywhere, Category = "Mode Common Settings")
		float bulletDamage = 40.f;

	UPROPERTY(EditAnywhere, Category = "Burst Mode Settings")
		int32 bulletsInOneBurst = 3;
	UPROPERTY(EditAnywhere, Category = "Burst Mode Settings")
		float gapBtwBullets = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* muzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* muzzleSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* hitEffect;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* hitSound;

	FTimerHandle burstTimer;
	bool inBurst;
	int amountShot;
};
