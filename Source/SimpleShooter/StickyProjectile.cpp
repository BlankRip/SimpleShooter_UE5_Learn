// Fill out your copyright notice in the Description page of Project Settings.


#include "StickyProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "ShooterCharacter.h"

void AStickyProjectile::BeginPlay() {
	Super::BeginPlay();

	expRangeSqr = explosionRange * explosionRange;
}

void AStickyProjectile::OnImpact(AActor* hitActor) {
	AttachToActor(hitActor, FAttachmentTransformRules::KeepWorldTransform);
}

void AStickyProjectile::TriggerSecondaryAction_Implementation() {
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionEffect, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), explosionSound, GetActorLocation());

	TArray<AActor*> actorsInDmgRange;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShooterCharacter::StaticClass(), actorsInDmgRange);
	for (AActor* actor : actorsInDmgRange) {
		if (actor == GetOwner() || actor == this)
			continue;
		
		float distanceToActor = (GetActorLocation() - actor->GetActorLocation()).SquaredLength();
		if (distanceToActor < expRangeSqr) {
			FDamageEvent damageEvent(UDamageType::StaticClass());
			actor->TakeDamage(damage, damageEvent, Cast<APawn>(GetOwner())->GetController(), this);
		}
	}
	Destroy();
}
