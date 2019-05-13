@echo off
set origdir=%cd%
for %%I in (.) do set CurrDirName=%%~nxI
echo %CurrDirName%
if "%CurrDirName%" NEQ "build" (
  cd build
  set "changecd=true"
)

conan install --build=missing -s build_type=Debug -s compiler.version=15 -s arch=x86_64 -pr ..\profile.py ..
cmake -G "Visual Studio 15 2017 Win64" ..

if "%changecd%" == "true" (
  cd %origdir%
)