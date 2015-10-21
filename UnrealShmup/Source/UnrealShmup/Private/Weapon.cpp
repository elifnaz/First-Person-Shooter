// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealShmup.h"
#include "Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "AssaultWeapon.h"

AWeapon::AWeapon(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, "WeaponMesh");
	RootComponent = WeaponMesh;

}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound)
	{
		AC = UGameplayStatics::PlaySoundAttached(Sound, RootComponent);
	}
	return AC;
}

void AWeapon::OnStartFire(){

		FireAC = PlayWeaponSound(FireLoopSound);
		MuzzleSC = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, RootComponent, TEXT("MuzzleFlashSocket"));

}

void AWeapon::OnStopFire(){


	FireAC->Stop();
	PlayWeaponSound(FireFinishSound);
	MuzzleSC->DeactivateSystem();
}