// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "SimpleProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleProjectile : public AProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void OnImpact(AActor* hitActor) override;
};
