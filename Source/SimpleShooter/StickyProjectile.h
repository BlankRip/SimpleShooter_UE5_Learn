// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "StickyProjectile.generated.h"

UCLASS()
class SIMPLESHOOTER_API AStickyProjectile : public AProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void OnImpact(AActor* hitActor) override;

public:
	virtual void TriggerSecondaryAction_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
		float explosionRange = 200.f;
	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* explosionEffect;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* explosionSound;

	float expRangeSqr;
};
