// Copyright Epic Games, Inc. All Rights Reserved.

namespace UnrealBuildTool.Rules
{
	public class InAppPerchaseBlueprintSupport : ModuleRules
	{
		public InAppPerchaseBlueprintSupport(ReadOnlyTargetRules Target) : base(Target)
		{

			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"Engine",
					"BlueprintGraph",
					"InAppPerchase"
					// ... add other public dependencies that you statically link with here ...
				}
			);

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"CoreUObject"
					// ... add private dependencies that you statically link with here ...
				}
			);
		}
	}
}
