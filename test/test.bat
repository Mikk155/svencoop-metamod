@echo off

cd ..

cmake --build build --config Debug

if errorlevel 1 (
    pause
    exit /b 1
)

cd build
cd Debug
TestPluginLoader.exe

pause
