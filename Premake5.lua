---common vars we have to manually define
SDL_LINK_PATH_DEBUG = ""
SDL_LINK_PATH_RELEASE = ""
SDL_LINK_PATH_DIST = ""

VULKAN_SDK_MANUAL_OVERRIDE = "C:/VulkanSDK/1.3.283.0/Include"

--searches for a Vulkan SDK on the system and loads it

--common includes everyone will use
FMT_INCLUDE = "Venders/FMT/include"
GLM_INCLUDE = "Venders/GLM"
SDL_INCLUDE = "Venders/SDL/include"
VK_BOOTSTRAP_INCLUDE = "Venders/VKBootstrap/src"
STB_INCLUDE = "Venders/STB"
VOLK_INCLUDE = "Venders/Volk"
VMA_INCLUDE = "Venders/VMA/include"

BTD_INCLUDE = "BTDSTD3/includes"

---The STD library for Bytes The Dust projects
project "BTDSTD"
location ""
kind "StaticLib"
language "C++"

files 
{
---base code
"includes/**.h",
"src/**.c",
"includes/**.hpp",
"src/**.cpp",

"Venders/VKBootstrap/src/VkBootstrap.cpp",
"Venders/VKBootstrap/src/VkBootstrap.h",
"Venders/VKBootstrap/src/VkBootstrapDispatch.h",
"Venders/Volk/volk.c",
"Venders/Volk/volk.h",

}

includedirs 
{
---base code
"includes",
GLM_INCLUDE,
FMT_INCLUDE,
SDL_INCLUDE,

VK_BOOTSTRAP_INCLUDE,
STB_INCLUDE,
VOLK_INCLUDE,
VMA_INCLUDE,
VULKAN_SDK_MANUAL_OVERRIDE
}

links
{
}


defines
{
    "VK_NO_PROTOTYPES",
"GLM_FORCE_DEPTH_ZERO_TO_ONE",
"GLM_FORCE_RADIANS",
"GLM_ENABLE_EXPERIMENTAL",
}


flags
{
"MultiProcessorCompile",
"NoRuntimeChecks",
}


buildoptions
{
"/utf-8",
}


--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Window_Build",
"VK_USE_PLATFORM_WIN32_KHR",
"Desktop_Build",
}

filter "system:linux"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"Linux_Build",
"VK_USE_PLATFORM_XLIB_KHR",
"Desktop_Build",
}


    filter "system:mac"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"


defines
{
"MacOS_Build",
"VK_USE_PLATFORM_MACOS_MVK",
"Desktop_Build",
}

--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"


links
{
    SDL_LINK_PATH_DEBUG
}

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"



links
{
    SDL_LINK_PATH_RELEASE
}

filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"


defines
{
"NDEBUG",
}


flags
{
"LinkTimeOptimization",
}


links
{
    SDL_LINK_PATH_DIST
}