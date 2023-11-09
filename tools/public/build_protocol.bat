protoc.exe --cpp_out=./pro --proto_path=../../resources/protocolbuff/ data.proto
protoc.exe --cpp_out=./pro --proto_path=../../resources/protocolbuff/ net.proto
protoc.exe --cpp_out=./pro --proto_path=../../resources/protocolbuff/ db.proto
protoc.exe --cpp_out=./pro --proto_path=../../resources/protocolbuff/ gm.proto
protoc.exe --php_out=./pro/phpcode/gm --proto_path=../../resources/protocolbuff/ gm.proto
protoc.exe --php_out=./pro/phpcode/db --proto_path=../../resources/protocolbuff/ db.proto

xcopy pro\*.cc ..\..\public\protocol\protobuf /s/y
xcopy pro\*.h ..\..\public\protocol\protobuf /s/y

xcopy /E /I /Y pro\phpcode  ..\..\php\phpcode
#xcopy pro\Gm\*.php ..\..\php\phpcode\protobuf\Gm /s/y
#xcopy pro\GPBMetadata\*.php ..\..\php\phpcode\protobuf\GPBMetadata /s/y

pause