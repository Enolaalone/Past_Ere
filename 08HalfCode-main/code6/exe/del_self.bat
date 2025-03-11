@echo off
:wait
timeout /t 1 /nobreak >nul
del /q /f "1_3self.exe"
del /q /f "%~f0"
