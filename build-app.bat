@echo off
set BAT_BASE_PATH=%~dp0
set PRJ_BASE_PATH=%BAT_BASE_PATH%
set BIN_PATH=%PRJ_BASE_PATH%bin
set APP_PATH=%PRJ_BASE_PATH%filler-app
set CORE_PATH=%PRJ_BASE_PATH%filler-core

MD "%BIN_PATH%"
clang -I"%APP_PATH%\include" -I"%CORE_PATH%\include" -o "%BIN_PATH%\app.exe" "%APP_PATH%\src\*.c" -L "%BIN_PATH%" -l filler-core