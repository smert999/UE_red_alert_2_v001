// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE_RTS_Course : ModuleRules
{
	public UE_RTS_Course(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"EnhancedInput",
			"UMG",
			"NavigationSystem",
			"AIModule",
			"GameplayAbilities",
			"GameplayTasks",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { 
			"Slate", 
			"SlateCore",
			"CommonUI"
		});
	}
}