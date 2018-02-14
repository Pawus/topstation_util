@echo off
rem arguments : 1-"nom"

rem suppression de la source ODBC
reg delete "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\ODBC Data Sources" /v "%~1" /f
reg delete "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /f

echo.
echo OK Source ODBC %~1 supprimee
pause