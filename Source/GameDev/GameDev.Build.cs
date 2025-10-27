// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameDev : ModuleRules
{
	public GameDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// Aggiungi "GameplayTags" qui
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
			// vuoto per ora
		});

		// // Uncomment se usi Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// // Uncomment se usi OnlineSubsystem
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
	}
}


/*
// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameDev : ModuleRules
{
	public GameDev(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
*/