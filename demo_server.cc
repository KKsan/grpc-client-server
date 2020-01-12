#include <string>
#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "messages.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::Status;
using demo::ProtoRequest;
using demo::ProtoResponse;
using demo::Greeter;

class GreeterImpl final : public Greeter::Service {
    public:
        //constructor
        explicit GreeterImpl() {

        }
        
        Status SayHello(ServerContext* context, const ProtoRequest* request, ProtoResponse* response) {
            //handle request
            std::cout << request->id() << std::endl;
            std::cout << request->query() << std::endl;
            query = request->query();

            //generate response
            response->set_id(1234);
            response->add_values(25);
            response->add_values(36);
            response->add_values(49);
            return Status::OK;
        }
    
    private:
        std::string query;
};

void RunServer() {
    std::string server_address("127.0.0.1::5555");
    GreeterImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}

