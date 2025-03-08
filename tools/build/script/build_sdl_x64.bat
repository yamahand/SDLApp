@echo off

REM Set the environment for x64
call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

REM Build the solution in Debug mode
msbuild "c:\Users\a1829\source\SDLApp\external\SDL3\VisualC\SDL.sln" /p:Configuration=Debug /p:Platform=x64

REM Build the solution in Release mode
msbuild "c:\Users\a1829\source\SDLApp\external\SDL3\VisualC\SDL.sln" /p:Configuration=Release /p:Platform=x64
