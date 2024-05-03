// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter123.h"

// Sets default values
AMyCharacter123::AMyCharacter123()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter123::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter123::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, TEXT("BBBBBBBBBBBBBBB"));
}

// Called to bind functionality to input
void AMyCharacter123::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

