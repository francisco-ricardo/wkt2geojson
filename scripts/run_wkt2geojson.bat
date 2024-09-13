@echo off
REM "I have been crucified with Christ and I no longer live,
REM but Christ lives in me. The life I now live in the body,
REM I live by faith in the Son of God, who loved me and
REM gave himself for me." Galatians 2:20 (NIV)

REM Function to print usage information
:print_help
    echo Usage: %0 ^<full_path_to_wkt_file^>
    echo.
    echo This script facilitates the execution of the 'wkt2geojson' program
    echo inside a Docker container. It allows users to specify the absolute or
    echo relative path to an input file, which is then processed by the
    echo 'wkt2geojson' command. The script dynamically determines the project
    echo directory and mounts both the project directory and the directory
    echo containing the input file into the Docker container. It ensures that
    echo the input file is accessible within the container and executes the
    echo 'wkt2geojson' program with the '-i' option for the input file.
    echo.
    echo Options:
    echo   -h    Show this help message and exit
    echo.
    echo Arguments:
    echo   full_path_to_wkt_file    Absolute or relative path to the input file
    echo.
    echo Requirements:
    echo   Docker
    echo   'wkt2geojson' Docker image
    echo.
    echo Example:
    echo   run-wkt2geojson.bat C:\absolute\path\to\file
    goto :EOF

REM Check for help option
if "%~1"=="-h" (
    call :print_help
    exit /b 0
)

REM Check if the input file was provided
if "%~1"=="" (
    echo Error: Input file path is required.
    call :print_help
    exit /b 1
)

set FILE_PATH=%~1

REM Check if the input file exists
if not exist "%FILE_PATH%" (
    echo Error: File %FILE_PATH% not found.
    exit /b 1
)

REM Absolute path to the directory where the script is located
set SCRIPT_DIR=%~dp0
set PROJECT_DIR=%SCRIPT_DIR%

REM Directory containing the input file
for %%I in ("%FILE_PATH%") do set INPUT_DIR=%%~dpI
for %%I in ("%FILE_PATH%") do set INPUT_FILE=%%~nxI

REM Execute the command in the container
docker run --rm ^
    -v "%PROJECT_DIR%:/app" ^
    -v "%INPUT_DIR%:/data" ^
    -w /data ^
    wkt2geojson /app/application/bin/wkt2geojson -i "/data/%INPUT_FILE%"

