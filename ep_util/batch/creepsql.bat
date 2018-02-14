@echo off
rem arguments : 1-"nom" 2-"pilote" 3-"serveur" 4-"port" 5-"base" 6-"user" 7-"pwd" 8-"ssl" 9-"Description"

rem verification du driver ODBC
reg query "HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBCINST.INI\%~2" /v Driver > %cd%\tmpdllpg.txt
for /f "tokens=3 delims=	" %%i in ('"findstr "Driver" %cd%\tmpdllpg.txt"') do set dllname=%%i
del %cd%\tmpdllpg.txt
if "%dllname%" == "" goto nodriver
echo.
echo dll : %dllname%

rem creation de la source ODBC
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\ODBC Data Sources" /v "%~1" /t REG_SZ /d %2 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Driver" /t REG_SZ /d "%dllname%" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "CommLog" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Debug" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Fetch" /t REG_SZ /d 100 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Optimizer" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Ksqo" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UniqueIndex" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UseDeclareFetch" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UnknownSizes" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "TextAsLongVarchar" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UnknownsAsLongVarchar" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "BoolsAsChar" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Parse" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "CancelAsFreeStmt" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "MaxVarcharSize" /t REG_SZ /d 255 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "MaxLongVarcharSize" /t REG_SZ /d 8190 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ExtraSysTablePrefixes" /t REG_SZ /d dd_; /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Description" /t REG_SZ /d "%~9" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Database" /t REG_SZ	/d "%~5" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Servername" /t REG_SZ /d "%~3" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Port" /t REG_SZ /d "%~4" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Username" /t REG_SZ /d "%~6" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UID" /t REG_SZ /d "%~6" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Password" /t REG_SZ /d "%~7" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ReadOnly" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ShowOidColumn" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "FakeOidIndex" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "RowVersioning" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ShowSystemTables" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "Protocol" /t REG_SZ /d 7.4-1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ConnSettings" /t REG_SZ /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "DisallowPremature" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UpdatableCursors" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "LFConversion" /t REG_SZ /d 1 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "TrueIsMinus1" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "BI" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "AB" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "ByteaAsLongVarBinary" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "UseServerSidePrepare" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "LowerCaseIdentifier" /t REG_SZ /d 0 /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "SSLmode" /t REG_SZ /d "%~8" /f
reg add "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\%~1" /v "XaOpt" /t REG_SZ /d 1 /f
goto fin


:nodriver
echo.
echo Driver %~2 inexistant
pause
exit

:fin
echo.
echo OK Source ODBC %~1 cree
pause