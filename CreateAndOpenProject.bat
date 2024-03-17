@echo off
setlocal

set location=%cd%
cd "%~dp0"
if not exist ".\dev\" (
	mkdir dev
)
cd dev && cmake .. && start "" ".\Junia.sln"
cd %location%

endlocal
