// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sparta_Practice_8 : ModuleRules
{
	public Sparta_Practice_8(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
    }
}
