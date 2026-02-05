@echo off
REM N64 Development Clean Script
REM Cleans build artifacts from libdragon and tiny3d

setlocal EnableDelayedExpansion

set PROJECT_DIR=%~dp0
set MSYS_BASH=C:\msys64\usr\bin\bash.exe

if not exist "%MSYS_BASH%" (
    echo ERROR: MSYS2 not found
    exit /b 1
)

set "MSYS_PROJECT_DIR=%PROJECT_DIR:\=/%"
set "MSYS_PROJECT_DIR=%MSYS_PROJECT_DIR:C:=/c%"

echo === Cleaning N64 Development Libraries ===
echo.

echo Cleaning libdragon...
%MSYS_BASH% -lc "cd '%MSYS_PROJECT_DIR%libdragon' && make clean 2>/dev/null; git checkout -- . 2>/dev/null; git clean -fd 2>/dev/null"

echo Cleaning tiny3d...
%MSYS_BASH% -lc "cd '%MSYS_PROJECT_DIR%tiny3d' && make clean 2>/dev/null; git checkout -- . 2>/dev/null; git clean -fd 2>/dev/null"

echo.
echo Clean complete!
