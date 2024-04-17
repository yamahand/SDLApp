@echo off
setlocal

pushd "%~dp0"

call build_vs2022_Debug.bat
call build_vs2022_Release.bat

popd
endlocal
