// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;
using static UnrealBuildTool.ModuleRules.Framework;

public class InAppPerchase : ModuleRules
{
	public InAppPerchase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        if (Target.Platform == UnrealTargetPlatform.VisionOS)
        {
            string RevenusCatVisionDir = Path.Combine(ModuleDirectory, "ThirdParty/VisionOS/");
            PublicSystemIncludePaths.AddRange(
                new string[] {
                        RevenusCatVisionDir + "include",
                }
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                "RevenueCat",
                Path.Combine(RevenusCatVisionDir, "RevenueCat.framework.zip"),
                FrameworkMode.LinkAndCopy
                )
            );
        }else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            string RevenusCatVisionDir = Path.Combine(ModuleDirectory, "ThirdParty/IOS/");
            PublicSystemIncludePaths.AddRange(
                new string[] {
                        RevenusCatVisionDir + "include",
                }
            );
            PublicAdditionalFrameworks.Add(
                new Framework(
                "RevenueCat",
                Path.Combine(RevenusCatVisionDir, "RevenueCat.framework.zip"),
                FrameworkMode.LinkAndCopy
                )
            );
        }

        PublicIncludePaths.AddRange(
			new string[] {
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
                "CoreUObject",
                "Engine",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
			);

	}
}
