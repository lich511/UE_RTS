// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIControllerR.generated.h"
/**
 * 
 */
UCLASS()
class CRESERCH2_API AMyAIControllerR : public AAIController
{
	GENERATED_BODY()

public:
	//ok
	AMyAIControllerR(const FObjectInitializer& ObjectInitializer);
public:
	//main logick AI
	void MainLogic();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// fucking c++
	virtual void BeginPlay() override;
};
