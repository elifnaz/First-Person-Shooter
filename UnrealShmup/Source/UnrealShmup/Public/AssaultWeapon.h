// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_UCLASS_BODY()

public:

	void OnStartFire() override;
	void OnStopFire() override;

	UPROPERTY(EditAnywhere)
	float FireRate;

	UPROPERTY(EditAnywhere)
	float WeaponRange;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* WeaponPC;

	float Damage = 2.0f;

protected:

	void WeaponTrace();

};
