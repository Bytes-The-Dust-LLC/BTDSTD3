#the script for generating the BTDSTD project
#move into the root next to your other project generation python scripts
#or tweak the "sys.path.insert(1, "BTDScripts")"
#or make any other tweaks this is all yours :3

import sys

sys.path.insert(1, "BTDScripts")
import PremakeGenerate as PremakeGen
import Premake_Defines
import Premake_Links
import Premake_BuildOptions
import Premake_Flags

#defines the link name
PROJECT_NAME = "BTDSTD"

#defines the include directory
PROJECT_INCLUDE_DIR = "includes"

#generates the project
def GeneratePremake(SDLIncludeDir, FMTIncludeDir, GLMIncludeDir, SDLLinkPath_Debug, SDLLinkPath_Release, SDLLinkPath_Dist):
    premakeCode = ""

    #KAR main exe project
    KARProject = PremakeGen.Project()
    KARProject.name = PROJECT_NAME
    KARProject.kind = "StaticLib"
    KARProject.language = "C++"
        
    KARProject.location = ""
    KARProject.desc = "The STD library for Bytes The Dust projects"

    KARProject.binaryOutput = PremakeGen.GenerateDefaultBinaryOutputPath() + "/BTDSDK"

    premakeCode = premakeCode + KARProject.GenerateProjectHeaderString()

    KARProject.sourceFiles = []
    premakeCode = premakeCode + KARProject.GenerateProjectSourceString()

    KARProject.includeDirs = {SDLIncludeDir,
FMTIncludeDir, GLMIncludeDir}
    premakeCode = premakeCode + KARProject.GenerateProjectIncludeString()

    premakeCode = premakeCode + Premake_Links.GenerateLinksString({})

    premakeCode = premakeCode + Premake_Defines.GenerateDefinesString({
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL"
})

    premakeCode = premakeCode + Premake_Flags.GenerateFlagsString({"NoRuntimeChecks",
    "MultiProcessorCompile"})

    premakeCode = premakeCode + Premake_BuildOptions.GenerateBuildOptionFlagsString({"/utf-8"})

    premakeCode = premakeCode + """

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
"""

    premakeCode = premakeCode + Premake_Defines.GenerateDefinesString({"Window_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_WIN32_KHR"})

    premakeCode = premakeCode + """
filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
"""

    premakeCode = premakeCode + Premake_Defines.GenerateDefinesString({"Linux_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_XLIB_KHR"})

    premakeCode = premakeCode + """

    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"
"""

    premakeCode = premakeCode + Premake_Defines.GenerateDefinesString({"MacOS_Build",
        "Desktop_Build",
        "VK_USE_PLATFORM_MACOS_MVK"})

    premakeCode = premakeCode + """
--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"
"""

    premakeCode = premakeCode + Premake_Links.GenerateLinksString({SDLLinkPath_Debug})

    premakeCode = premakeCode + """
filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

"""

    premakeCode = premakeCode + Premake_Links.GenerateLinksString({SDLLinkPath_Release})

    premakeCode = premakeCode + """
filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"
"""

    premakeCode = premakeCode + Premake_Defines.GenerateDefinesString({"NDEBUG"})
    premakeCode = premakeCode + Premake_Flags.GenerateFlagsString({"LinkTimeOptimization"})

    premakeCode = premakeCode + Premake_Links.GenerateLinksString({SDLLinkPath_Dist})


    return premakeCode