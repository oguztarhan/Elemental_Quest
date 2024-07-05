// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Elemental_Quest : ModuleRules
{
	public Elemental_Quest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "UMG" });


        PrivateDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add("C:/Program Files/Epic Games/UE_5.3/Engine/Source/Runtime");
        PublicIncludePaths.Add("C:/Program Files/Epic Games/UE_5.3/Engine/Source/Runtime/Engine/Classes/GameFramework");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
