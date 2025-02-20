@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

echo =============================
echo   Bakery Source Code Steps
echo =============================

:: List all step_*.cpp files
set count=0
for %%f in (src/step_*.cpp) do (
    set /a count+=1
    set "file[!count!]=%%f"
    echo !count!. %%f
)

:: If no files found, exit
if %count%==0 (
    echo No C++ source files found.
    pause
    exit /b
)

:: Get user input
echo.
set /p choice=Enter number of file to compile and run: 

:: Validate input
if not defined file[%choice%] (
    echo Invalid choice. Exiting...
    pause
    exit /b
)

set "filename=!file[%choice%]!"

:: Compile the selected file
echo Compiling %filename%...
g++ -std=c++17 -o program.exe src/%filename%

:: Check if compilation was successful
if %errorlevel% neq 0 (
    echo Compilation failed.
    pause
    exit /b
)

:: Run the compiled program
echo Running program.exe...
echo ------------------------------------------------
program.exe
echo ------------------------------------------------

:: Pause before closing
pause

:: Clear screen
cls