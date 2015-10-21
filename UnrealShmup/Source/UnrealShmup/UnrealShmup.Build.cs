// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UnrealShmup : ModuleRules
{
	public UnrealShmup(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
"InputCore", "AIModule" });
    }
}
