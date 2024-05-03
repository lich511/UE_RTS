// Copyright Epic Games, Inc. All Rights Reserved.

#include "CReserch2GameMode.h"
#include "CReserch2Character.h"
#include "UObject/ConstructorHelpers.h"

ACReserch2GameMode::ACReserch2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
