@echo off

cd..

cmake --build build --config Debug

cd build
cd Debug
TestPluginLoader.exe

pause
