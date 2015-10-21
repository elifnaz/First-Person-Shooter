// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIEnemyController.h"
#include "DwarfCharacter.h"
#include "AIDwarfController.generated.h"

enum class EDwarfPlayState : short
{
	EStart,
	EChase,
	EAttack, 
	EDead

};

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
	void Tick(float DeltaSeconds) override;
	void ChangeState(EDwarfPlayState NewState);
	EDwarfPlayState GetCurrentState() const;

	UPROPERTY(EditAnywhere)
		float Range = 150.0f;

	ADwarfCharacter* MyDwarf;

private:
	EDwarfPlayState CurrentState;
	void HandleNewState(EDwarfPlayState NewState);
};

FORCEINLINE EDwarfPlayState AAIDwarfController::GetCurrentState() const
{
	return CurrentState;
}