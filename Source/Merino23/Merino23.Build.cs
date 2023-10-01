// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Merino23 : ModuleRules
{
	public Merino23(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem","Navmesh"});
		PrivateDependencyModuleNames.AddRange(new[] { "MerinoStatics" });
	}
}