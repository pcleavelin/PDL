@echo off

cargo clean
cargo build

if %ERRORLEVEL% GEQ 1 (
	echo libpdl failed to compile:
	type target\debug\cl_log.txt
	
	EXIT /B %ERRORLEVEL%
)

call .\win32test_rust.bat

if %ERRORLEVEL% GEQ 1 EXIT /B %ERRORLEVEL%

rem .\target\win32test\testapi.exe