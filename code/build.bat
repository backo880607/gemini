@echo off
title test build command
set VCINSTALLDIR=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build
call "%VCINSTALLDIR%\vcvarsall.bat" amd64
nmake