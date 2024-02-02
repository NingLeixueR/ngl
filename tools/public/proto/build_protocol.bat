protoc.exe --experimental_allow_proto3_optional  --cpp_out=./pro data.proto
protoc.exe --experimental_allow_proto3_optional  --cpp_out=./pro net.proto
protoc.exe --experimental_allow_proto3_optional  --cpp_out=./pro db.proto
protoc.exe --experimental_allow_proto3_optional  --cpp_out=./pro gm.proto
protoc.exe --experimental_allow_proto3_optional --php_out=./pro/phpcode/gm gm.proto
protoc.exe --experimental_allow_proto3_optional --php_out=./pro/phpcode/db db.proto

protoc.exe --experimental_allow_proto3_optional  --csharp_out=./pro net.proto
protoc.exe --experimental_allow_proto3_optional  --csharp_out=./pro db.proto

xcopy pro\*.cc ..\..\..\public\cpp\protocol\protobuf /s/y
xcopy pro\*.h ..\..\..\public\cpp\protocol\protobuf /s/y
xcopy pro\*.cs ..\..\..\public\csharp\protobuf /s/y

xcopy /E /I /Y pro\phpcode  ..\..\..\php\
#xcopy pro\Gm\*.php ..\..\php\phpcode\protobuf\Gm /s/y
#xcopy pro\GPBMetadata\*.php ..\..\php\phpcode\protobuf\GPBMetadata /s/y

pause