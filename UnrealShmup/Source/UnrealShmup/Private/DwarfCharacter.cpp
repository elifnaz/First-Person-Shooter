// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealShmup.h"
#include "DwarfCharacter.h"
#include "AIDwarfController.h"


ADwarfCharacter::ADwarfCharacter(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	AIControllerClass = AAIDwarfController::StaticClass();
	
}

void ADwarfCharacter::StartAttack()
{
	if (!IsDestroyed){
		float Duration = PlayAnimMontage(AttackAnim);
		GetWorldTimerManager().SetTimer(this, &ADwarfCharacter::CauseDamage, Duration, true);
	}
}

void ADwarfCharacter::StopAttack()
{

	StopAnimMontage(AttackAnim);
	GetWorldTimerManager().ClearTimer(this, &ADwarfCharacter::CauseDamage);

}

void ADwarfCharacter::CauseDamage(){

	UGameplayStatics::GetPlayerPawn(this, 0)->TakeDamage(10.0f, FDamageEvent(), GetInstigatorController(), this);

}

float ADwarfCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(Damage, DamageEvent,
		EventInstigator, DamageCauser);
	if (ActualDamage > 0.0f)
	{
		Health -= ActualDamage;
		if (Health <= 0.0f)
		{
			((AAIDwarfController*)Controller)->ChangeState(EDwarfPlayState::EDead);
			// We're dead
			bCanBeDamaged = false; // Don't allow further damage
			// TODO: Process death
			StopAttack();
			float time = PlayAnimMontage(DeathAnim);
			GetWorldTimerManager().SetTimer(this, &ADwarfCharacter::DestroyCharacter, time - 0.25f, true);
			Controller->UnPossess();
		}
		
	}
	return ActualDamage;
}

void ADwarfCharacter::DestroyCharacter(){

	IsDestroyed = Destroy();
}