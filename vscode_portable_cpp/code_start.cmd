@echo off

:: important variable; propagates to the whole environment
set VSCodeDirectory=%~d0%~p0

:: update PATH
set PATH=%PATH%;%VSCodeDirectory%;%VSCodeDirectory%\mingw64\bin

:: start VSCode
code