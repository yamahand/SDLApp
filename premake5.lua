workspace "SDLApp"
configurations { "Debug", "Release" }
    platforms "x64"
    location "build"

filter { "platforms:x64" }
    system "windows"
    architecture "x86_64"

filter { "configurations:Debug" }
    defines { "DEBUG", "PB_DEBUG" }
    symbols "On"

filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "On"

local EXTERNAL_DIR = "./external"
local SDL_INC_DIR = EXTERNAL_DIR .. "/SDL/include"
local SDL_LIB_DIR = EXTERNAL_DIR .. "/SDL/lib/%{cfg.platform}/%{cfg.buildcfg}"
local LIB_DIR = "./lib"
local LIB_SRC_DIR = LIB_DIR .. "/src"
local LIB_BIN_DIR = LIB_DIR .. "/lib"

project "lib"
    location "build"
    targetdir "./lib/lib/%{cfg.platform}/%{cfg.buildcfg}"
    kind "StaticLib"
    libdirs  { SDL_LIB_DIR }
    includedirs { SDL_INC_DIR }
    links { "SDL3.lib" }
    files { LIB_SRC_DIR .. "/**.h", LIB_SRC_DIR .. "/**.hpp", LIB_SRC_DIR .. "/**.cpp", LIB_SRC_DIR .. "/**.cc", LIB_SRC_DIR .. "/**.inl" }
    language "C++"
    cppdialect "C++latest"


project "app"
    location "build"
    dependson "external"
    targetdir "./runtime/%{cfg.buildcfg}"
    debugdir "./runtime/%{cfg.buildcfg}"
    filter "Release"
        kind "WindowedApp"
    filter "Debug"
        kind "ConsoleApp"
    filter {}

    language "C++"
    cppdialect "C++latest"
    files { "src/**.h", "src/**.hpp", "src/**.cpp", "src/**.cc", "src/**.inl", "src/**.hlsl", "src/**.hlsli" }
    libdirs  { LIB_BIN_DIR .. "/%{cfg.platform}/%{cfg.buildcfg}" }
    includedirs { "./src", LIB_SRC_DIR }
    pchheader "stdafx.h"
    pchsource "src/stdafx.cpp"
    links { "lib" }

    filter { "files:**.hlsl", "files:**.hlsli" }
        flags "ExcludeFromBuild"
        shadermodel "5.0"
    filter { "files:**Pixel**.hlsl" }
        removeflags "ExcludeFromBuild"
        shadertype "Pixel"
        shaderentry "BasicPS"
        shadermodel "5.0"
    filter { "files:**Vertex**.hlsl" }
        removeflags "ExcludeFromBuild"
        shadertype "Vertex"
        shaderentry "BasicVS"
        shadermodel "5.0"
    filter {}
    -- copy a file from the objects directory to the target directory
    postbuildcommands {
        "{COPYFILE} %[" .. SDL_LIB_DIR .. "/SDL3.dll] %[%{!cfg.targetdir}]"
    }
