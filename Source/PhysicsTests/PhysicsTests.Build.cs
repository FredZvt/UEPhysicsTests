// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PhysicsTests : ModuleRules
{
	public PhysicsTests(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine",
			"Chaos", "PhysicsCore",
			"InputCore", "EnhancedInput"
		});
	}
}
