// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleProjectile.h"

void ASimpleProjectile::OnImpact(AActor* hitActor) {
	Super::OnImpact(hitActor);

	FDamageEvent damageEvent(UDamageType::StaticClass());
	/*FHitResult hitResult;
	FPointDamageEvent pointDmgEvent(damage, hitResult, GetActorForwardVector(), nullptr);*/
	hitActor->TakeDamage(damage, damageEvent, Cast<APawn>(GetOwner())->GetController(), this);
	Destroy();
}
