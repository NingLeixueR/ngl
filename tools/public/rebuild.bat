xcopy ..\..\bin\Debug\rebuild.exe .\ /s/y
rebuild.exe ../../server/out_rebuild/core/ub.cpp ../../public 
cd ../../bin/Debug
makeproto.exe