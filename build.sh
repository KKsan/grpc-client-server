make clean
make messages.grpc.pb.cc messages.pb.cc
make


#generate message classes
#protoc --proto_path=protos --cpp_out=. protos/messages.proto

#generate service classes
#protoc --proto_path=protos --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin protos/messages.proto
