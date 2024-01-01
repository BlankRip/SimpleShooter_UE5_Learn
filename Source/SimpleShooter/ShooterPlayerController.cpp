// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "ShooterCharacter.h"

void AShooterPlayerController::BeginPlay() {
	Super::BeginPlay();

	hud = CreateWidget(this, hudClass, TEXT("Player HUD"));
	if (hud)
		hud->AddToViewport();
	else
		UE_LOG(LogTemp, Error, TEXT("Hud class was null"));

	if (AShooterCharacter* player = Cast<AShooterCharacter>(GetPawn())) {
		UUserWidget* pickUpInfo = CreateWidget(this, pickUpInfoClass, TEXT("Pick-Up Info"));
		if (pickUpInfo)
			player->SetPickUpInfoWidget(pickUpInfo);
		else
			UE_LOG(LogTemp, Error, TEXT("Pick up Infor class was null"));
	}
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner) {
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	hud->RemoveFromViewport();
	if (bIsWinner) {
		UUserWidget* winScreen = CreateWidget(this, winScreenClass, TEXT("Win Screen"));
		if (winScreen)
			winScreen->AddToViewport();
		else
			UE_LOG(LogTemp, Error, TEXT("Win Screen was null"));
	} else {
		UUserWidget* loseScreen = CreateWidget(this, loseScreenClass, TEXT("Lose Screen"));
		if (loseScreen)
			loseScreen->AddToViewport();
		else
			UE_LOG(LogTemp, Error, TEXT("Lose Screen was null"));
	}

	GetWorldTimerManager().SetTimer(restartTimer, this, &APlayerController::RestartLevel, restartDelay);
}
