// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealShmup.h"
#include "AIDwarfController.h"
#include "DwarfCharacter.h"
#include "UnrealShmupCharacter.h"

void AAIDwarfController::BeginPlay()
{
	Super::BeginPlay();
	ChangeState(EDwarfPlayState::EStart);


}

void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	MyDwarf = Cast<ADwarfCharacter>(GetPawn());
	ChangeState(EDwarfPlayState::EAttack);
}

void AAIDwarfController::Tick(float DeltaSeconds)
{
	if (GetCurrentState() == EDwarfPlayState::EDead)
		return;
	if (GetCurrentState() == EDwarfPlayState::EStart)
		ChangeState(EDwarfPlayState::EChase);
	else if (GetCurrentState() == EDwarfPlayState::EAttack){
		if (UGameplayStatics::GetPlayerPawn(this, 0)->GetDistanceTo(MyDwarf) > Range){
			MyDwarf->StopAttack();
			ChangeState(EDwarfPlayState::EChase);
		}
	}
}

void AAIDwarfController::ChangeState(EDwarfPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);

}

void AAIDwarfController::HandleNewState(EDwarfPlayState NewState)
{
	switch (NewState)
	{
	case EDwarfPlayState::EStart:
		break;
	case EDwarfPlayState::EChase: 	
		MoveToActor(UGameplayStatics::GetPlayerPawn(this, 0));
		break;
	case EDwarfPlayState::EAttack:
		MyDwarf->StartAttack();
		break;
	}

}