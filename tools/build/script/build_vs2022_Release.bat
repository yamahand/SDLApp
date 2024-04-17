@echo off
setlocal

pushd "%~dp0"

if not defined DevEnvDir (
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
) else (
    exit /b
)
)

pushd ..\..\..\build

MSBuild SDLApp.sln /t:build /p:Configuration=Release;Platform="x64"

popd
popd
