@echo off
setlocal enableextensions enabledelayedexpansion

set "built_exe=c:\work\projects\vs\xecho\x64\Debug\xecho.exe"
set "space_exe=foo bar\xecho.exe"

if not exist "%built_exe%" (
    echo built_exe not found: "%built_exe%"
    exit /b 1
)
if not exist "foo bar" mkdir "foo bar"
if exist "%space_exe%" (
    del "%space_exe%" ||  (
        echo space_exe could not be deleted: "%space_exe%"
        exit /b 1
    )
)
(copy "%built_exe%" "%space_exe%" >NUL) || (
    echo built_exe could not be copied to "%space_exe%"
    exit /b 1
)
@echo on
@echo -------[space_exe]-----------
"%space_exe%" "a b" c
@echo -------[/space_exe]----------

@echo -------[built_exe]-----------
"%built_exe%" "a b" c
@echo -------[/built_exe]----------

