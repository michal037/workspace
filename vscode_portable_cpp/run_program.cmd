@echo off

if "%~1"=="" (
	echo use: run_program.cmd ^<program^>
	goto :endOfTheScript
)

if exist %~1 (
	%~1
	echo.
) else (
	echo No program found to run!
)

:endOfTheScript