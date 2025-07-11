@echo off
cmake --build build

cd build
cd Debug
TestPluginLoader.exe
pause
