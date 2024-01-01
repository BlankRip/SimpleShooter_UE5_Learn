// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class AGunBase;
class IPickUpInterface;
class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator, AActor* DamageCauser) override;

	void Shoot();
	void ShootSecondary();
	void Reload();
	void SwitchFireingMode();

	void SetPickUpInfoWidget(UUserWidget* wiget);
	void SetPickable(IPickUpInterface* pickItem, FString displayInfo);
	void ClearPickable();
	bool HasEmptyGunSlot();
	void PickUpGun(TSubclassOf<AGunBase> gunClass);

	UFUNCTION(BlueprintCallable)
		void Heal(float recoveryAmount);
	UFUNCTION(BlueprintPure)
		bool IsDead() const;
	UFUNCTION(BlueprintPure)
		float GetHealthPercent() const;
	UFUNCTION(BlueprintPure)
		FString GetPickUpInstruction() const;
	UFUNCTION(BlueprintPure)
		AGunBase* GetCurrentGun() const;

private:
	void CreateOrReplaceWithNewGun(TSubclassOf<AGunBase> gunClass, int32 atIndex);
	void SwapGunTo(int32 swapToIndex);
	void CycleGuns(float axisValue);
	void CycleGunUp();
	void CycleGunDown();

	void MoveForward(float axisValue);
	void MoveRight(float axisValue);
	void LookUpRate(float axisValue);
	void LookRightRate(float axisValue);
	void Interact();

	UPROPERTY(EditAnywhere)
		float rotationRate = 25.f;
	UPROPERTY(EditDefaultsOnly)
		float maxHealth = 100.f;
	UPROPERTY(VisibleAnywhere)
		float health;
	UPROPERTY(EditDefaultsOnly)
		int32 maxGunsHeld = 2;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AGunBase> startGunClass;
	UPROPERTY()
		TArray<AGunBase*> myGuns;
	UPROPERTY()
		UUserWidget* pickUpInfoWidget = nullptr;

	int32 currentGun;
	UObject* pickUpInRange;
	FString pickUpInstructions;
};
