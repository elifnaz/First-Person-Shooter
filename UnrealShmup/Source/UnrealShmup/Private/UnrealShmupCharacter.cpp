// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealShmup.h"
#include "UnrealShmupCharacter.h"

AUnrealShmupCharacter::AUnrealShmupCharacter(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AUnrealShmupCharacter::BeginPlay()
{
	// Call base class BeginPlay
	Super::BeginPlay();
	// Spawn the weapon, if one was specified
	if (WeaponClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// Need to set rotation like this because otherwise gun points down
			// NOTE: This should probably be a blueprint parameter
			FRotator Rotation(0.0f, 0.0f, -90.0f);
			// Spawn the Weapon
			MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector,
				Rotation, SpawnParams);
			if (MyWeapon)
			{
				// This is attached to "WeaponPoint" which is defined in the skeleton
				// NOTE: This should probably be a blueprint parameter
				MyWeapon->WeaponMesh->AttachTo(GetMesh(), TEXT("WeaponPoint"));
				MyWeapon->MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
			}
		}
	}
}

void AUnrealShmupCharacter::OnFireStart()
{
	if (MyWeapon){
		MyWeapon->OnStartFire();
	}

}


void AUnrealShmupCharacter::OnFireStop()
{
	if (MyWeapon)
		MyWeapon->OnStopFire();

}

float AUnrealShmupCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent,
		EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		if (Health <= 0.0f)
		{
			// We're dead
			bCanBeDamaged = false; // Don't allow further damage
			// TODO: Process death
			float time = PlayAnimMontage(DeathAnim);
			GetWorldTimerManager().SetTimer(this, &AUnrealShmupCharacter::DestroyCharacter, DeathAnim->SequenceLength - 0.25f, true);
			//Controller->UnPossess();
			APlayerController * controller = Cast<APlayerController>(GetController());
			controller->SetCinematicMode(true, true, true);

		}
	}
	return ActualDamage;
}


void AUnrealShmupCharacter::DestroyCharacter(){

	GetMesh()->Deactivate();
}


bool AUnrealShmupCharacter::IsDead(){

	if (Health <= 0.0f)
		return true;
	else return false;
}