@echo off

if not exist out/bakery.exe (
    echo Did not find executable!
    exit /b 1
)

start out/bakery.exe