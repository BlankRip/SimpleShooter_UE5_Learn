// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"

void AKillEmAllGameMode::PawnKilled(APawn* killedPawn) {
	Super::PawnKilled(killedPawn);

	UE_LOG(LogTemp, Warning, TEXT("Pawn Killed"));
	APlayerController* playerController = Cast<APlayerController>(killedPawn->GetController());
	if (playerController)
		EndGame(false);

	for (AShooterAiController* controller : TActorRange<AShooterAiController>(GetWorld())) {
		if (!controller->IsDead())
			return;
	}
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool playerWon) {
	for (AController* controller : TActorRange<AController>(GetWorld())) {
		bool isCurrentWinner = controller->IsPlayerController() == playerWon;
		controller->GameHasEnded(controller->GetPawn(), isCurrentWinner);
	}
}
