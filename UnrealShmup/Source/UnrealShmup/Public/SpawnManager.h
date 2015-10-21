// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API ASpawnManager : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = Spawn)
	TArray <ATargetPoint*> TargetPoints;

	UPROPERTY(EditAnywhere, Category = Spawn)
		TSubclassOf <ACharacter> CharacterToSpawn;

	UPROPERTY(EditAnywhere, Category = Spawn)
		float MinSpawnTime;

	UPROPERTY(EditAnywhere, Category = Spawn)
		float MaxSpawnTime;

		void BeginPlay() override;
		void Spawn();
		float GetRandomDelay();

		UPROPERTY(BluePrintReadOnly, Category = Spawn)
		bool ShouldSpawn = true;

		UPROPERTY(BluePrintReadWrite, Category = Spawn)
			ATargetPoint* SpawnLocation;
	
};

