@echo off
set IDE="Visual Studio 16 2019"
set SOURCE_DIR="%cd%"
set BUILD_DIR="%cd%\build"
cmd /c "cmake -G %IDE% -S %SOURCE_DIR% -B %BUILD_DIR%"
pause