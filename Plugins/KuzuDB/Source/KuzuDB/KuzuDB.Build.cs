using UnrealBuildTool;
using System.IO;

public class KuzuDB : ModuleRules
{
    public KuzuDB(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        // Adding public and private include paths
        PublicIncludePaths.Add(Path.Combine(ModuleDirectory, "Public"));
        PrivateIncludePaths.Add(Path.Combine(ModuleDirectory, "Private"));


        // Adding public dependency modules
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
            }
        );

        // Platform-specific settings
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            // Correcting the path to the Libraries directory
            string LibrariesPath = Path.Combine(ModuleDirectory, "Libraries");
            string KuzuLib = Path.Combine(LibrariesPath, "kuzu_shared.lib");
            string KuzuDll = Path.Combine("$(PluginDir)/Binaries/Win64", "kuzu_shared.dll");

            // Check if the .lib file exists
            if (File.Exists(KuzuLib))
            {
                PublicAdditionalLibraries.Add(KuzuLib);
            }
            else
            {
                throw new BuildException($"Library file not found: {KuzuLib}");
            }

            // Add the DLL for delay loading and runtime dependencies
            RuntimeDependencies.Add("$(TargetOutputDir)/kuzu_shared.dll", KuzuDll);
            PublicDelayLoadDLLs.Add(KuzuDll);
            RuntimeDependencies.Add(KuzuDll);
        }

        // Module settings
        bTreatAsEngineModule = true;
        bEnableUndefinedIdentifierWarnings = false;
        bUseUnity = false;
        bEnableExceptions = true;

    }
}
