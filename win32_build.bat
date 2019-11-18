@echo off

mkdir build
pushd build

cl.exe -Zi ../src/Win32/main.cpp /link user32.lib gdi32.lib /entry:mainCRTStartup

popd