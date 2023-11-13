xcopy ..\..\..\bin\Debug\IDL.exe .\ /s/y
xcopy ..\..\..\bin\Release\IDL.exe .\ /s/y
IDL.exe
xcopy idlfile\*.h ..\..\..\public\protocol\ /s/y
xcopy idlfile\*.cpp ..\..\..\public\protocol\ /s/y
pause