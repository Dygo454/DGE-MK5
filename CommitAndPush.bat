@echo off
set /p "q=Would you like to compile(y/n): "
if "%q%"=="" (set q=n)
if "%q%"=="y" make
if "%q%"=="Y" make
set /p "cm=Enter Commit Message: "
if "%cm%"=="" (set cm=Unspecified Commit)
make github-nocompile commit="%cm%"
TIMEOUT 10