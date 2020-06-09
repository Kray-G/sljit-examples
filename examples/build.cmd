echo off

if "%1"=="" goto ERROR

if not exist libudis86.dll call :MKUDIS86
if not exist libudis86.dll goto ERROR
cl /I ..\sljit /DSLJIT_CONFIG_AUTO=1 %1 ..\sljit\sljitLir.c libudis86.lib

:END
exit /b 0

:MKUDIS86
cd ..\udis86\BuildVS2017
call buildVS2017.bat
cd ..\..\examples
copy /y ..\udis86\BuildVS2017\Build\Bin\x64\libudis86.lib .\
copy /y ..\udis86\BuildVS2017\Build\Bin\x64\libudis86.dll .\
exit /b 0

:ERROR
echo Usage: build.cmd [source file]
exit /b 1
