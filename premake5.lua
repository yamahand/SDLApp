include("./tools/build/script/build_paths.lua")

location(build_root)
targetdir(build_bin)
objdir(build_obj)

workspace "SDLApp"
configurations { "Debug", "Release" }
    platforms "x64"

filter { "platforms:x64" }
    system "windows"
    architecture "x86_64"

filter { "configurations:Debug" }
    defines { "DEBUG", "PB_DEBUG" }
    symbols "On"

filter { "configurations:Release" }
    defines { "NDEBUG" }
    optimize "On"

include "external/imgui.lua"
-- include "external/eigen.lua"
include "external/DirectXMath.lua"

local EXTERNAL_DIR = "./external"
local SDL_INC_DIR = EXTERNAL_DIR .. "/SDL/include"
local SDL_LIB_DIR = EXTERNAL_DIR .. "/SDL/lib/%{cfg.platform}/%{cfg.buildcfg}"
local LIB_DIR = "./lib"
local LIB_SRC_DIR = LIB_DIR .. "/src"

group("lib")
project "lib"
    kind "StaticLib"
    dependson { "lib", "imgui"}
    libdirs  { SDL_LIB_DIR, build_bin }
    includedirs { LIB_SRC_DIR, SDL_INC_DIR, EXTERNAL_DIR, IMGUI_DIR, DIRECTXMATH_INC_DIR }
    links { "SDL3.lib", "imgui.lib" }
    files { LIB_SRC_DIR .. "/**.h", LIB_SRC_DIR .. "/**.hpp", LIB_SRC_DIR .. "/**.cpp", LIB_SRC_DIR .. "/**.cc", LIB_SRC_DIR .. "/**.inl" }
    language "C++"
    cppdialect "C++latest"


group("app")
project "app"
    dependson "lib"
    targetdir "./runtime/%{cfg.buildcfg}"
    debugdir "./runtime/%{cfg.buildcfg}"
    filter "Release"
        kind "WindowedApp"
    filter "Debug"
        kind "ConsoleApp"
    filter {}
    forceincludes { "stdafx.h" }

    language "C++"
    cppdialect "C++latest"
    files { "src/**.h", "src/**.hpp", "src/**.cpp", "src/**.cc", "src/**.inl", "src/**.hlsl", "src/**.hlsli" }
    libdirs  { build_bin }
    includedirs { "./src", LIB_SRC_DIR, EXTERNAL_DIR, DIRECTXMATH_INC_DIR, IMGUI_DIR }
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
