::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::
:: @file      CreateAndOpenProject.bat
:: @brief     Contains the script to create and open the project files on
::            windows
:: @author    Max Hager
:: @date      17.03.2024
:: @copyright © Max Hager, 2024. All right reserved.
::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

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
