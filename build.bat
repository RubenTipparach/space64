@echo off
REM Build Space64 N64 Game
REM This builds only your game, not libdragon/tiny3d

setlocal EnableDelayedExpansion

set PROJECT_DIR=%~dp0
set MSYS_BASH=C:\msys64\usr\bin\bash.exe

if not exist "%MSYS_BASH%" (
    echo ERROR: MSYS2 not found. Run setup.bat first.
    exit /b 1
)

set "MSYS_PROJECT_DIR=%PROJECT_DIR:\=/%"
set "MSYS_PROJECT_DIR=%MSYS_PROJECT_DIR:C:=/c%"

echo === Building Space64 ===
echo.

%MSYS_BASH% -lc "export PATH='/ucrt64/bin:/usr/bin:$PATH' && export N64_INST='%MSYS_PROJECT_DIR%/n64-toolchain' && cd '%MSYS_PROJECT_DIR%' && make"

if errorlevel 1 (
    echo.
    echo Build FAILED!
    exit /b 1
)

echo.
echo === Build Complete ===
echo.
echo ROM created: space64.z64
echo.
echo To run: Use Ares emulator (https://ares-emu.net/)
