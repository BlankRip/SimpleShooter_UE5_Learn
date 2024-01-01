// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

private:
	UPROPERTY(EditAnywhere)
		float restartDelay = 5.f;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> hudClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> winScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> loseScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> pickUpInfoClass;

	UPROPERTY()
		UUserWidget* hud;		
	FTimerHandle restartTimer;
};
