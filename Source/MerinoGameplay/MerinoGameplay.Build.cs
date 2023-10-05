// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class MerinoGameplay : ModuleRules
{
	public MerinoGameplay(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(new[] { "Core", "CoreUObject", "Engine","MerinoStatics","Merino23"});
	}
}