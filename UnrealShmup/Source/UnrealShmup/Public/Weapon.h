// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API AWeapon : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Weapon)
	USkeletalMeshComponent * WeaponMesh;

public:

	virtual void OnStartFire();
	virtual void OnStopFire();

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireLoopSound;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* FireFinishSound;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* MuzzleFX;

	APawn * MyPawn;

protected:

	UAudioComponent* PlayWeaponSound(USoundCue* PlayWeaponSound);

	UPROPERTY(Transient)
	UAudioComponent* FireAC;

	UPROPERTY(Transient)
	UParticleSystemComponent* MuzzleSC;

};
