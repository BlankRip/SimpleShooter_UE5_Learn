// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger(bool primary);
	void SwitchFieringMode();
	void Reload();

	virtual bool CanFire();
	virtual void FireBulletModeA();
	virtual void TriggerBulletSecondaryModeA();
	virtual void FireBulletModeB();
	virtual void TriggerBulletSecondaryModeB();

	UFUNCTION(BlueprintPure)
		FString GetGunName() const;
	UFUNCTION(BlueprintPure)
		FString GetGunModeName() const;
	UFUNCTION(BlueprintPure)
		int GetAmmoInClip() const;
	UFUNCTION(BlueprintPure)
		int GetAvailableAmmo() const;
protected:
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* mesh;

	UPROPERTY(EditDefaultsOnly, Category = "Gun Stats")
		int magSize = 6;
	int inClip;
	bool fieringModeB = false;

private:
	void TriggerSecondaryProperty();

	UPROPERTY(VisibleAnywhere)
		USceneComponent* root;
	UPROPERTY(EditDefaultsOnly, Category = "Gun Stats")
		int maxAmmo = 100;
	UPROPERTY(EditDefaultsOnly, Category = "Gun Stats")
		FString gunName = "Gun Name";
	UPROPERTY(EditDefaultsOnly, Category = "Gun Stats")
		FString modeName_A = "Gun Mode A";
	UPROPERTY(EditDefaultsOnly, Category = "Gun Stats")
		FString modeName_B = "Gun Mode B";

	int availableAmmo;
	FString currentModeName;

};
