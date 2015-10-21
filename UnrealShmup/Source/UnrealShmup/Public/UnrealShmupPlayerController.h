// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "UnrealShmupPlayerController.generated.h"

UCLASS()
class AUnrealShmupPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	//void OnSetDestinationPressed();
	//void OnSetDestinationReleased();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void UpdateMouseLook();

	void OnFireStart();
	void OnFireStop();

};


