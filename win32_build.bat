call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64

echo %OUT_DIR%

rem Build static PDL library
cl.exe -Zi /c /Fd%OUT_DIR%\ /Fo%OUT_DIR%\ src/Win32/win32_pdl.c /link user32.lib gdi32.lib > target\debug\cl_log.txt
pushd %OUT_DIR%
lib.exe /OUT:pdl.lib win32_pdl.obj
popd