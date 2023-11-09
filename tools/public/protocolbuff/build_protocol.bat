protoc.exe --cpp_out=./pro data.proto
protoc.exe --cpp_out=./pro net.proto
protoc.exe --cpp_out=./pro db.proto
protoc.exe --cpp_out=./pro gm.proto
protoc.exe --php_out=./pro/phpcode/gm gm.proto
protoc.exe --php_out=./pro/phpcode/db db.proto

xcopy pro\*.cc ..\..\..\public\protocol\protobuf /s/y
xcopy pro\*.h ..\..\..\public\protocol\protobuf /s/y

xcopy /E /I /Y pro\phpcode  ..\..\..\php\phpcode
#xcopy pro\Gm\*.php ..\..\php\phpcode\protobuf\Gm /s/y
#xcopy pro\GPBMetadata\*.php ..\..\php\phpcode\protobuf\GPBMetadata /s/y

pause