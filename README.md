# gRPC Client Server
Dummy client server built with gRPC and protobuf

Project Contributors (ordered by last name):
* [Xizhao Deng](xizhaode@usc.edu)

## Synopsis
The protobuf messages are defined in `protos/messages.proto`. The `demo_client` is running on `localhost:6666`. It constructs a `ProtoRequest` message and sends it to `demo_server` running on `localhost:5555`. The `demo_server` sends back a `ProtoResponse` message. This is to show the most simple use case of gRPC with synchronized messaging interaction between client and server.

## Instruction
1. Clone this repo
```
git clone git@github.com:KKsan/grpc-client-server.git
```
2. Build the code
```
cd grpc-client-server/
./build.sh
```
3. Execute the client and server
```
./demo_client
./demo_server
```

## Other notes
Currently running on OSX Catalina 10.15.2 with protobuf 3.11.2 and grpc 1.26.0 will error out with `segfault 11`
