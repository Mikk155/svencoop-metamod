@echo off
setlocal

:: Check if SolutionDir is already set and non-empty
if not defined SolutionDir (
    :: Only set Solution-Dir if it's not already set
    SET "SolutionDir=%~dp0.."
)

:: Ensure the path ends with a backslash
if not "%SolutionDir:~-1%"=="\" SET "SolutionDir=%SolutionDir%\"

cd /d "%SolutionDir%"

call git submodule update --init "%SolutionDir%thirdparty\capstone_fork"


:: --- LÍNEAS MEJORADAS: Parcheamos el archivo usando PowerShell y especificando la codificación UTF-8 ---
echo [INFO] Aplicando parches a CMakeLists.txt de Capstone...

:: PARCHE 1: Actualiza la versión mínima de CMake para que sea compatible
powershell -Command "(Get-Content -Encoding utf8 '%SolutionDir%thirdparty\capstone_fork\CMakeLists.txt') -replace 'cmake_minimum_required\(VERSION 2.6\)', 'cmake_minimum_required(VERSION 3.5)' | Set-Content -Encoding utf8 '%SolutionDir%thirdparty\capstone_fork\CMakeLists.txt'"

:: PARCHE 2: Comenta la política antigua (CMP0048) para asegurar que no cause problemas
powershell -Command "(Get-Content -Encoding utf8 '%SolutionDir%thirdparty\capstone_fork\CMakeLists.txt') -replace 'cmake_policy \(SET CMP0048 OLD\)', '#cmake_policy (SET CMP0048 OLD)' | Set-Content -Encoding utf8 '%SolutionDir%thirdparty\capstone_fork\CMakeLists.txt'"

:: --- Compila para Debug ---
call cmake -S "%SolutionDir%thirdparty\capstone_fork" -B "%SolutionDir%thirdparty\build\capstone\x86\Debug" -A Win32 -DCMAKE_INSTALL_PREFIX="%SolutionDir%thirdparty\install\capstone\x86\Debug" -DCAPSTONE_AARCH64_SUPPORT=FALSE -DCAPSTONE_ARCHITECHTURE_DEFAULT=FALSE -DCAPSTONE_ARM64_SUPPORT=FALSE -DCAPSTONE_ARM_SUPPORT=FALSE -DCAPSTONE_BPF_SUPPORT=FALSE -DCAPSTONE_BUILD_CSTEST=FALSE -DCAPSTONE_BUILD_CSTOOL=FALSE -DCAPSTONE_BUILD_DIET=FALSE -DCAPSTONE_BUILD_SHARED=FALSE -DCAPSTONE_BUILD_STATIC=TRUE -DCAPSTONE_BUILD_STATIC_RUNTIME=TRUE -DCAPSTONE_BUILD_TESTS=FALSE -DCAPSTONE_DEBUG=TRUE -DCAPSTONE_EVM_SUPPORT=FALSE -DCAPSTONE_INSTALL=FALSE -DCAPSTONE_M680X_SUPPORT=FALSE -DCAPSTONE_M68K_SUPPORT=FALSE -DCAPSTONE_MIPS_SUPPORT=FALSE -DCAPSTONE_MOS65XX_SUPPORT=FALSE -DCAPSTONE_OSXKERNEL_SUPPORT=FALSE -DCAPSTONE_PPC_SUPPORT=FALSE -DCAPSTONE_RISCV_SUPPORT=FALSE -DCAPSTONE_SH_SUPPORT=FALSE -DCAPSTONE_SPARC_SUPPORT=FALSE -DCAPSTONE_SYSZ_SUPPORT=FALSE -DCAPSTONE_TMS320C64X_SUPPORT=FALSE -DCAPSTONE_IMS320C64X_SUPPORT=FALSE -DCAPSTONE_TRICORE_SUPPORT=FALSE -DCAPSTONE_USE_DEFAULT_ALLOC=TRUE -DCAPSTONE_WASM_SUPPORT=FALSE -DCAPSTONE_X86_ATT_DISABLE=FALSE -DCAPSTONE_X86_REDUCE=FALSE -DCAPSTONE_X86_SUPPORT=TRUE -DCAPSTONE_XCORE_SUPPORT=FALSE

call cmake --build "%SolutionDir%thirdparty\build\capstone\x86\Debug" --config Debug --target install

endlocal