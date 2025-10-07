@echo off
echo ==============================
echo Building mgc...
echo ==============================

if not exist bin mkdir bin

REM failed when using wildcard as argument src/*.cpp. FUTURE REF - make CMake file to comile.
g++ -Iinclude src\commit.cpp src\hash_utils.cpp src\hash.cpp src\repo.cpp src\req-handler.cpp src\staging.cpp src\utils.cpp main.cpp ^
 -Llib -lssl -lcrypto -lws2_32 -lcrypt32 -lbcrypt -lcurl ^
 -o bin\mgc.exe

if %errorlevel% neq 0 (
    echo.
    echo ❌ Build failed!
    echo Press any key to close...
    pause >nul
    exit /b %errorlevel%
)

REM !!! DLL needs to be present in root folder due to static linking issues
REM Check and copy dll if exists, else return error
if exist libcurl-x64.dll (
    copy /Y libcurl-x64.dll bin\ >nul
    echo ✅ Copied libcurl-x64.dll to bin\
) else (
    echo ⚠️  libcurl-x64.dll not found in project root!
)

echo ✅ Build complete! Executable is in bin\
echo ==============================
