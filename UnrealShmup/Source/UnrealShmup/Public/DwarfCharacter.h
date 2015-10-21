// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnemyCharacter.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage * AttackAnim;

	void StartAttack();
	void StopAttack();

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float Health = 20.0f;

	float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	void DestroyCharacter();
	void CauseDamage();
	bool IsDestroyed = false;

	UPROPERTY(EditDefaultsOnly)
		UAnimMontage * DeathAnim;
	
};
