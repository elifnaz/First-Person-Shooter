// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "UnrealShmup.h"
#include "UnrealShmupGameMode.h"
#include "UnrealShmupPlayerController.h"

AUnrealShmupGameMode::AUnrealShmupGameMode(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = AUnrealShmupPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/Blueprints/MyCharacter.MyCharacter_C'"));
	if (PlayerPawnBPClass.Object != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Object;

	}
}