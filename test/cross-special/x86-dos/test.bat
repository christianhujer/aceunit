@echo off
err=0

simple
if not errorlevel 1 goto simple_success
echo simple failed
set err=1
:simple_success

setjmp
if not errorlevel 1 goto setjmp_success
echo setjmp failed
set err=1
:setjmp_success
