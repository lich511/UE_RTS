// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestUnitC.generated.h"

UCLASS()
class CRESERCH2_API ATestUnitC : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* TrigerMesh;
public:
	// Sets default values for this character's properties
	ATestUnitC();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Team;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	float DeltaTimeValue = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	bool isAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FString orderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	FVector orderTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	AActor* orderEnemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
