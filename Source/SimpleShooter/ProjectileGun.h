// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GunBase.h"
#include "ProjectileGun.generated.h"

class AProjectileBase;

UCLASS()
class SIMPLESHOOTER_API AProjectileGun : public AGunBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	AProjectileGun();

	virtual void FireBulletModeA() override;
	virtual void FireBulletModeB() override;
	virtual void TriggerBulletSecondaryModeB() override;

private:
	AProjectileBase* FireProjectile(TSubclassOf<AProjectileBase> projectileClass);
	bool GunTrace(FHitResult& hit, FVector& shotDirection);

	UPROPERTY(VisibleAnywhere)
		USceneComponent* fieringPoint;
	UPROPERTY(EditDefaultsOnly, Category = "Projectiles")
		TSubclassOf<AProjectileBase> simpleProjectileClass;
	UPROPERTY(EditDefaultsOnly, Category = "Projectiles")
		TSubclassOf<AProjectileBase> stickyProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* muzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* muzzleSound;

	TArray<AProjectileBase*> stickiesShot;
};
