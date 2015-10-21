// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Weapon.h"
#include "UnrealShmupCharacter.generated.h"

UCLASS(Blueprintable)
class AUnrealShmupCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TSubclassOf<AWeapon> WeaponClass;

public:
	void BeginPlay() override;
	void OnFireStart();
	void OnFireStop();

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage * DeathAnim;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float Health = 100.0f;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	void DestroyCharacter();
	bool IsDead();


private:

	AWeapon * MyWeapon;


};

