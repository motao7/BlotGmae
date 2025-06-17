// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BlotGame : ModuleRules
{
	public BlotGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				"BlotGame"
			}
		);
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);
		
		PublicDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreOnline",
				"CoreUObject",
				"ApplicationCore",
				"Engine",
				"PhysicsCore",
				"GameplayTags",
				"GameplayTasks",
				"GameplayAbilities",
				"AIModule",
				"ModularGameplay",
				"DataRegistry",
				"ReplicationGraph",
				"GameFeatures",
				"SignificanceManager",
				"Hotfix",
				"Niagara",
				"ControlFlows",
				"PropertyPath",
				
				"ModularGameplayActors"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"InputCore",
				"Slate",
				"SlateCore",
				"RenderCore",
				"DeveloperSettings",
				"EnhancedInput",
				"NetCore",
				"RHI",
				"Projects",
				"Gauntlet",
				"UMG",
				"CommonUI",
				"CommonInput",
				"AudioMixer",
				"NetworkReplayStreaming",
				"ClientPilot",
				"AudioModulation",
				"EngineSettings",
				"DTLSHandlerComponent", 
				
				"Experience",
				"ShooterCoreRuntime", "Team","CommonCamera","TagInput"
			}
		);
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[] {
			}
		);
		
		// Generate compile errors if using DrawDebug functions in test/shipping builds.
		PublicDefinitions.Add("SHIPPING_DRAW_DEBUG_ERROR=1");
		
		
		SetupGameplayDebuggerSupport(Target);
		SetupIrisSupport(Target);
	}
}
