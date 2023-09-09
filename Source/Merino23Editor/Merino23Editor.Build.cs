// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Merino23Editor : ModuleRules
{
	public Merino23Editor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "ComponentVisualizers"});
		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "UnrealEd", "ComponentVisualizers"}); 
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}