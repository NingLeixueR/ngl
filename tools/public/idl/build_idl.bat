xcopy ..\..\..\bin\Debug\IDL.exe .\ /s/y
xcopy ..\..\..\bin\Release\IDL.exe .\ /s/y
IDL.exe
xcopy idlfile\*.h ..\..\..\public\cpp\protocol\ /s/y
xcopy idlfile\*.cpp ..\..\..\public\cpp\protocol\ /s/y
xcopy idlfile\*.cs ..\..\..\public\csharp\csv\ /s/y
pause