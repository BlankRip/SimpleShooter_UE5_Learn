// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAiController.generated.h"


UCLASS()
class SIMPLESHOOTER_API AShooterAiController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		UBehaviorTree* aiBehavior;

	UBlackboardComponent* aiBlackboard;
	APawn* playerPawn;

	//UPROPERTY(EditAnywhere)
		//float acceptanceRadius = 250.f;
	//bool playerInSite;
};
