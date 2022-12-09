@echo off

w32tm /config /syncfromflags:domhier /update
w32tm /resync /force
tzutil /s UTC

pause