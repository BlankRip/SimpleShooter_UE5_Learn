// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SIMPLESHOOTER_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnImpact(AActor* hitActor);

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* hitEffect;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* hitSound;
	UPROPERTY(EditAnywhere)
		float damage = 60.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void TriggerSecondaryAction();
	virtual void TriggerSecondaryAction_Implementation();

private:
	UFUNCTION()
		void OnHitComponent(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere)
		USphereComponent* sphereComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere)
		UProjectileMovementComponent* movementComponent;
};
