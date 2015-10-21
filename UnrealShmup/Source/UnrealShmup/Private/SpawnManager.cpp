// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealShmup.h"
#include "SpawnManager.h"
#include "DwarfCharacter.h"

ASpawnManager::ASpawnManager(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	MinSpawnTime = 3.5f;

	MaxSpawnTime = 5.5f;
}



void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnLocation = TargetPoints.HeapTop();
	GetWorldTimerManager().SetTimer(this, &ASpawnManager::Spawn, GetRandomDelay(), false);

}


float ASpawnManager::GetRandomDelay()
{
	return FMath::FRandRange(MinSpawnTime, MaxSpawnTime);
}


void ASpawnManager::Spawn()
{
	if (CharacterToSpawn != NULL)
	
	{
		UWorld* const World = GetWorld();

		if (World)
		{
			ShouldSpawn = true;
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			FRotator SpawnRotation;

			ADwarfCharacter* const SpawnedCharacter = World->SpawnActor<ADwarfCharacter>(CharacterToSpawn, SpawnLocation->GetActorLocation(), SpawnRotation, SpawnParams);
			SpawnedCharacter->SpawnDefaultController();
			ShouldSpawn = false;
			GetWorldTimerManager().SetTimer(this, &ASpawnManager::Spawn, GetRandomDelay(), false);

		}
	}
}
