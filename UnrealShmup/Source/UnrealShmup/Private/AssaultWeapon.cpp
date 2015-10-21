// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealShmup.h"
#include "AssaultWeapon.h"
#include "DwarfCharacter.h"

AAssaultWeapon::AAssaultWeapon(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	FireRate = 0.1f;
	WeaponRange = 10000.0f;

}

void AAssaultWeapon::WeaponTrace()
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
	static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
	// Start from the muzzle's position
	FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
	// Get forward vector of MyPawn
	FVector Forward = MyPawn->GetActorForwardVector();
	// Calculate end position
	FVector EndPos = StartPos + Forward  * WeaponRange;
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;
	// This fires the ray and checks against all objects w/ collision
	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingle(Hit, StartPos, EndPos, TraceParams,
		FCollisionObjectQueryParams::AllObjects);
	// Did this hit anything?

	if (Hit.bBlockingHit)
	{

 		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), WeaponPC, Hit.ImpactPoint, GetActorRotation(), false);
		
		ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
		if (Dwarf)
		{
			Dwarf->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
		}
		
	}
}

void AAssaultWeapon::OnStartFire(){
	Super::OnStartFire();
	GetWorldTimerManager().SetTimer(this, &AAssaultWeapon::WeaponTrace, FireRate, true);

}

void AAssaultWeapon::OnStopFire(){
	Super::OnStopFire();
	GetWorldTimerManager().ClearTimer(this, &AAssaultWeapon::WeaponTrace);
}