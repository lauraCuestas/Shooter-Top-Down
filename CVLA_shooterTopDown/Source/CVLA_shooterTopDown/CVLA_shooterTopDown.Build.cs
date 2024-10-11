// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CVLA_shooterTopDown : ModuleRules
{
	public CVLA_shooterTopDown(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

	}
}
