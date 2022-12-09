@echo off

start "TEST 1" cmd /c "for /l %%i in () do (ping 1.1.1.1 -n 10) & cls"
start "TEST 2" cmd /c "for /l %%i in () do (ping 2.2.2.2 -n 10) & cls"
start "TEST 3" cmd /c "for /l %%i in () do (ping 3.3.3.3 -n 10) & cls"
