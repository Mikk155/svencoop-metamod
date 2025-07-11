@echo off
cmake --build build

cd build
cd Debug
LimitlessPotential.exe
pause
