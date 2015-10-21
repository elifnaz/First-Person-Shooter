// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealShmup.h"
#include "UnrealShmupPlayerController.h"
#include "UnrealShmupCharacter.h"

AUnrealShmupPlayerController::AUnrealShmupPlayerController(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AUnrealShmupPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	
	//MoveToMouseCursor();
	UpdateMouseLook();
	
}

void AUnrealShmupPlayerController::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		APawn* const Pawn = GetPawn();
		if (Pawn)
		{
			Pawn->AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);
		}
	}

}


void AUnrealShmupPlayerController::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		APawn* const Pawn = GetPawn();
		if (Pawn)
		{
			Pawn->AddMovementInput(FVector(0.0f, 1.0f, 0.0f), Value);
		}
	}

}

void AUnrealShmupPlayerController::UpdateMouseLook()
{

if (!(this->IsLookInputIgnored())){
	APawn* const Pawn = GetPawn();
	FHitResult Hit;

	if (Pawn)
	{
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			FVector vector = Hit.ImpactPoint - Pawn->GetActorLocation();
			vector.Z = 0.0f;
			vector.Normalize();
			FRotator rotator = vector.Rotation();
			Pawn->SetActorRotation(rotator);
		}
	}

}
}

void AUnrealShmupPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &AUnrealShmupPlayerController::OnFireStart);
	InputComponent->BindAction("Fire", IE_Released, this, &AUnrealShmupPlayerController::OnFireStop);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AUnrealShmupPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AUnrealShmupPlayerController::MoveToTouchLocation);

	InputComponent->BindAxis("MoveForward", this, &AUnrealShmupPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUnrealShmupPlayerController::MoveRight);
}

void AUnrealShmupPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AUnrealShmupPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AUnrealShmupPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

/*
void AUnrealShmupPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AUnrealShmupPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

*/

void AUnrealShmupPlayerController::OnFireStart(){

	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		AUnrealShmupCharacter * character = Cast<AUnrealShmupCharacter>(Pawn);
		
		if (!(character->IsDead())){

			character->OnFireStart();
		}
	}

}

void AUnrealShmupPlayerController::OnFireStop(){

	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		AUnrealShmupCharacter * character = Cast<AUnrealShmupCharacter>(Pawn);
		character->OnFireStop();
			
	}
}