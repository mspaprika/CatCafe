@echo off

:: Close Unreal Editor and Visual Studio
taskkill /IM UE4Editor.exe /F
taskkill /IM UE5Editor.exe /F
taskkill /IM devenv.exe /F

:: Delete Intermediate folders
rmdir /S /Q "Path\To\Your\UnrealProject\Intermediate"
rmdir /S /Q "Path\To\Your\UnrealProject\Saved"

:: Regenerate Visual Studio project files
"C:\Program Files\Epic Games\Launcher\Engine\Binaries\Win64\UnrealVersionSelector.exe" /projectfiles "Path\To\Your\UnrealProject.uproject"

:: Launch Visual Studio
start "" "C:\Path\To\Your\VisualStudioSolution.sln"
