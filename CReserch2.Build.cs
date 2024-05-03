// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CReserch2 : ModuleRules
{
	public CReserch2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
