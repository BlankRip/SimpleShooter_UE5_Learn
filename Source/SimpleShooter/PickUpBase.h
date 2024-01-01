// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUpInterface.h"
#include "PickUpBase.generated.h"

class USphereComponent;
class URotatingMovementComponent;

UCLASS()
class SIMPLESHOOTER_API APickUpBase : public AActor, public IPickUpInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PickUp_Implementation(AActor* caller) override;
	virtual bool CanPickUp_Implementation(AActor* caller) override;

private:
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
		USphereComponent* sphereComponent;
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* mesh;
	UPROPERTY(VisibleAnywhere)
		URotatingMovementComponent* rotationComponent;

protected:
	UPROPERTY(EditDefaultsOnly)
		FString pickUpInfoText = "No Text Set";
};
