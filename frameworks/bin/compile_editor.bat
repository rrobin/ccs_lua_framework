@echo off
set DIR=%~dp0
cd "%DIR%../.."
call %DIR%compile_scripts.bat -i src/ -o frameworks/runtime-src/bin/game.bat -m zip

