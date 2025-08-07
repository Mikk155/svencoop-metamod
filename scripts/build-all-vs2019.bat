@REM Yes i'm lazy to install vs2022 x[

@echo off

setlocal

set Output="..\build-cmake\x86\Release"

if not exist build (
    call build-bullet3-x86-Release.bat
    call build-capstone-x86-Release.bat
    call build-metamod-cmake-x86-Release-2019.bat
)

cd ..
cd build-cmake
cd x86

cmake --build Release --config Release --clean-first

if %ERRORLEVEL% NEQ 0 (
    echo ERROR
    pause
    exit /b %ERRORLEVEL%
)

@pause
