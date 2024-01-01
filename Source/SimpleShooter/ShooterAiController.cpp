// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAiController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	//if (LineOfSightTo(playerPawn)) {
	//	aiBlackboard->SetValueAsVector(TEXT("playerLocation"), playerPawn->GetActorLocation());
	//	aiBlackboard->SetValueAsVector(TEXT("lastKnowPlayerLocation"), playerPawn->GetActorLocation());
	//	/*MoveToActor(playerPawn, acceptanceRadius);
	//	if (!playerInSite) {
	//		SetFocus(playerPawn);
	//		playerInSite = true;
	//	}*/
	//} else {
	//	aiBlackboard->ClearValue(TEXT("playerLocation"));
	//	/*ClearFocus(EAIFocusPriority::Gameplay);
	//	StopMovement();
	//	playerInSite = false;*/
	//}
}

bool AShooterAiController::IsDead() {
	AShooterCharacter* controledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (controledCharacter)
		return controledCharacter->IsDead();

	return true;
}

void AShooterAiController::BeginPlay() {
	Super::BeginPlay();

	playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (aiBehavior) {
		RunBehaviorTree(aiBehavior);
		aiBlackboard = GetBlackboardComponent();
		aiBlackboard->SetValueAsVector(TEXT("startLocation"), GetPawn()->GetActorLocation());
	}
	//playerInSite = false;
}
