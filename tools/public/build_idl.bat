xcopy ..\..\bin\Debug\IDL.exe .\ /s/y
xcopy ..\..\resources\idl\csvtable.idl .\ /s/y
IDL.exe
xcopy idlfile\*.h ..\..\public\protocol\ /s/y
xcopy idlfile\*.cpp ..\..\public\protocol\ /s/y
xcopy idlfile\*.cs ..\..\server\cs\core\ /s/y

del .\csvtable.idl
pause