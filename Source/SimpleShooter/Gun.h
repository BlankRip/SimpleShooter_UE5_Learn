// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystem;

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

private:
	bool GunTrace(FHitResult& hit, FVector& shotDirection);
	AController* GetOwnerController() const;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* root;
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* mesh;
	UPROPERTY(EditAnywhere)
		UParticleSystem* muzzleFlash;
	UPROPERTY(EditAnywhere)
		USoundBase* muzzleSound;
	UPROPERTY(EditAnywhere)
		UParticleSystem* hitEffect;
	UPROPERTY(EditAnywhere)
		USoundBase* hitSound;
	UPROPERTY(EditAnywhere)
		float maxRange = 1000.f;
	UPROPERTY(EditAnywhere)
		float damage = 10.f;

};
