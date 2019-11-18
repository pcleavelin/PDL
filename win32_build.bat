@echo off

mkdir build
pushd build

cl.exe -Zi /Fe ../src/Win32/main.c /link user32.lib gdi32.lib /entry:mainCRTStartup

popd