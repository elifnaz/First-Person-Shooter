// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class UNREALSHMUP_API AHealthBar : public AHUD
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere)
	float Health;

	void UpdateHealth();
	
	
};
