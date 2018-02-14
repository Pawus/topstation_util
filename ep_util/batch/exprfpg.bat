reg export "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\RegistreFoncierPG" %cd%\rfoncier.reg
reg query "HKEY_CURRENT_USER\Software\ODBC\ODBC.INI\RegistreFoncierPG" > %cd%\rfoncier.txt