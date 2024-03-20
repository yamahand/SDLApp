@echo off
pushd "%~dp0"
tools\build\bin\premake5.exe /file=./premake5.lua vs2022
popd
