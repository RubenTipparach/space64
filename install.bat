@echo off
REM N64 Development Environment Setup Script
REM This script downloads and installs the N64 toolchain locally

setlocal EnableDelayedExpansion

set PROJECT_DIR=%~dp0
set TOOLCHAIN_DIR=%PROJECT_DIR%n64-toolchain
set TOOLCHAIN_URL=https://github.com/DragonMinded/libdragon/releases/download/toolchain-continuous-prerelease/gcc-toolchain-mips64-win64.zip

echo === N64 Development Environment Setup ===
echo.

REM Check if toolchain already exists
if exist "%TOOLCHAIN_DIR%\bin\mips64-elf-gcc.exe" (
    echo Toolchain already installed at %TOOLCHAIN_DIR%
    echo Skipping download...
    goto :check_msys
)

REM Create toolchain directory
if not exist "%TOOLCHAIN_DIR%" mkdir "%TOOLCHAIN_DIR%"

echo Downloading N64 toolchain...
curl -L "%TOOLCHAIN_URL%" -o "%TOOLCHAIN_DIR%\toolchain.zip"
if errorlevel 1 (
    echo ERROR: Failed to download toolchain
    exit /b 1
)

echo Extracting toolchain...
cd /d "%TOOLCHAIN_DIR%"
tar -xf toolchain.zip
if errorlevel 1 (
    powershell -command "Expand-Archive -Path toolchain.zip -DestinationPath . -Force"
)
del toolchain.zip

:check_msys
REM Check for MSYS2
if not exist "C:\msys64\usr\bin\bash.exe" (
    echo.
    echo WARNING: MSYS2 not found at C:\msys64
    echo Please install MSYS2 from https://www.msys2.org/
    echo Then run: pacman -S make mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
    exit /b 1
)

REM Install MSYS2 dependencies
echo.
echo Installing MSYS2 build dependencies...
C:\msys64\usr\bin\bash.exe -lc "pacman -S --noconfirm --needed make mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make git"

echo.
echo === Setup Complete ===
echo.
echo Toolchain installed at: %TOOLCHAIN_DIR%
echo.
echo You can now run build.bat to build the game
echo.
