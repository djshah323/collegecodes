@echo off
setlocal
set here=%~dp0

set cp=%here%LamportClocks.jar;

set PATH=%here%;%here%\bin;%PATH%

java -cp "%cp%" org.bits.distributed.assignment.LogicalClkMain 5 1
endlocal
