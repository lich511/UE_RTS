// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUnitC.h"

// Sets default values
ATestUnitC::ATestUnitC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrigerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrigerMesh"));
	TrigerMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATestUnitC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestUnitC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATestUnitC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

