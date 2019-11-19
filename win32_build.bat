@echo off

mkdir build
mkdir build\lib
mkdir build\lib\win32
mkdir build\win32test

rem Build static PDL library
pushd build\lib\win32
cl.exe -Zi /c ../../../src/Win32/win32_pdl.c /link user32.lib gdi32.lib
lib.exe /OUT:pdl.lib win32_pdl.obj
popd

rem Build test application
pushd build\win32test
cl.exe -Zi ../../src/Win32/main.c /link user32.lib gdi32.lib ../lib/win32/pdl.lib /entry:mainCRTStartup
popd