pushd "%~dp0"

REM Install premake
if not exist ".premake" mkdir .premake
pushd ".premake"

REM Remove existing premake archive
if exist "premake.zip" del /F/Q premake.zip

REM Download premake
powershell -Command "(New-Object Net.WebClient).DownloadFile('https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip', 'premake.zip')"

REM Extract premake
powershell -Command "Expand-Archive -Path %cd%\premake.zip -DestinationPath %cd% -Force;"

REM Run premake to generate our project
premake5.exe --file=..\premake.lua vs2015

popd

popd
