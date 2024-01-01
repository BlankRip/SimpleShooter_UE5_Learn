// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GunBase.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"
#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PickUpInterface.h"


AShooterCharacter::AShooterCharacter() {
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay() {
	Super::BeginPlay();
	
	health = maxHealth;

	GetMesh()->HideBoneByName(TEXT("weapon_R"), EPhysBodyOp::PBO_None);
	myGuns.Reserve(maxGunsHeld);
	for (int32 i = 0; i < maxGunsHeld; i++)
		myGuns.Add(nullptr);
	currentGun = 0;
	CreateOrReplaceWithNewGun(startGunClass, currentGun);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("ShootSecondary"), EInputEvent::IE_Pressed, this, &AShooterCharacter::ShootSecondary);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("SwitchGunMode"), EInputEvent::IE_Pressed, this, &AShooterCharacter::SwitchFireingMode);
	PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Interact);
	PlayerInputComponent->BindAxis(TEXT("MouseScroll"), this, &AShooterCharacter::CycleGuns);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float dmgToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	health -= dmgToApply;
	if (health <= 0.f) {
		health = 0.f;
		GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>()->PawnKilled(this);
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	UE_LOG(LogTemp, Warning, TEXT("HP: %f"), health);
	return dmgToApply;
}

bool AShooterCharacter::IsDead() const {
	return health <= 0;
}

float AShooterCharacter::GetHealthPercent() const {
	return health/maxHealth;
}

FString AShooterCharacter::GetPickUpInstruction() const {
	return pickUpInstructions;
}

AGunBase* AShooterCharacter::GetCurrentGun() const {
	return myGuns[currentGun];
}

void AShooterCharacter::CreateOrReplaceWithNewGun(TSubclassOf<AGunBase> gunClass, int32 atIndex) {
	if (myGuns[atIndex])
		myGuns[atIndex]->Destroy();

	myGuns[atIndex] = GetWorld()->SpawnActor<AGunBase>(gunClass);
	myGuns[atIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("weaponSocket"));
	myGuns[atIndex]->SetOwner(this);
}

void AShooterCharacter::SwapGunTo(int32 swapToIndex) {
	myGuns[currentGun]->SetActorHiddenInGame(true);
	currentGun = swapToIndex;
	myGuns[currentGun]->SetActorHiddenInGame(false);
}

void AShooterCharacter::CycleGuns(float axisValue) {
	if (axisValue > 0)
		CycleGunUp();
	else if (axisValue < 0)
		CycleGunDown();
}

void AShooterCharacter::CycleGunUp() {
	int32 cycleTo = currentGun + 1;
	if (cycleTo >= myGuns.Num())
		cycleTo = 0;
	if (myGuns[cycleTo])
		SwapGunTo(cycleTo);
}

void AShooterCharacter::CycleGunDown() {
	int32 cycleTo = currentGun - 1;
	if (cycleTo < 0)
		cycleTo = myGuns.Num() - 1;
	if (myGuns[cycleTo])
		SwapGunTo(cycleTo);
}

void AShooterCharacter::MoveForward(float axisValue) {
	AddMovementInput(GetActorForwardVector() * axisValue);
}

void AShooterCharacter::MoveRight(float axisValue) {
	AddMovementInput(GetActorRightVector() * axisValue);
}

void AShooterCharacter::LookUpRate(float axisValue) {
	AddControllerPitchInput(axisValue * rotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float axisValue) {
	AddControllerYawInput(axisValue * rotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Interact() {
	if (pickUpInRange)
		IPickUpInterface::Execute_PickUp(pickUpInRange, this);
}

void AShooterCharacter::Shoot() {
	myGuns[currentGun]->PullTrigger(true);
}

void AShooterCharacter::ShootSecondary() {
	myGuns[currentGun]->PullTrigger(false);
}

void AShooterCharacter::Reload() {
	myGuns[currentGun]->Reload();
}

void AShooterCharacter::SwitchFireingMode() {
	myGuns[currentGun]->SwitchFieringMode();
}

void AShooterCharacter::Heal(float recoveryAmount) {
	health += recoveryAmount;
	if (health > maxHealth)
		health = maxHealth;
}

void AShooterCharacter::SetPickUpInfoWidget(UUserWidget* widget) {
	pickUpInfoWidget = widget;
}

void AShooterCharacter::SetPickable(IPickUpInterface* pickItem, FString displayInfo) {
	pickUpInRange = Cast<UObject>(pickItem);
	pickUpInstructions = displayInfo;
	if (pickUpInfoWidget)
		pickUpInfoWidget->AddToViewport();
}

void AShooterCharacter::ClearPickable() {
	pickUpInRange = nullptr;
	pickUpInstructions = "";
	if (pickUpInfoWidget)
		pickUpInfoWidget->RemoveFromViewport();
}

bool AShooterCharacter::HasEmptyGunSlot() {
	for (int32 i = 0; i < myGuns.Num(); i++) {
		if (myGuns[i] == nullptr)
			return true;
	}
	return false;
}

void AShooterCharacter::PickUpGun(TSubclassOf<AGunBase> gunClass) {
	int32 gunPos = -1;
	for (int32 i = 0; i < myGuns.Num(); i++) {
		if (myGuns[i] == nullptr) {
			gunPos = i;
			break;
		}
	}
	if (gunPos == -1)
		gunPos = currentGun;
	CreateOrReplaceWithNewGun(gunClass, gunPos);
	SwapGunTo(gunPos);
}