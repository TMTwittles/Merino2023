// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class Merino23EditorTarget : TargetRules
{
	public Merino23EditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_1;
		ExtraModuleNames.Add("Merino23");
		if (Type == TargetType.Editor)
		{
			ExtraModuleNames.AddRange(
				new string[]
				{
					"Merino23Editor"
				});
		}
	}
}
