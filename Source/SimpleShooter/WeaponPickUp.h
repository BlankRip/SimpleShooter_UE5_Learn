// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUpBase.h"
#include "WeaponPickUp.generated.h"

class AGunBase;

UCLASS()
class SIMPLESHOOTER_API AWeaponPickUp : public APickUpBase
{
	GENERATED_BODY()
	
public:
	virtual bool CanPickUp_Implementation(AActor* caller) override;
	virtual void PickUp_Implementation(AActor* caller) override;

private:
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGunBase> gunClassToGive;
};
