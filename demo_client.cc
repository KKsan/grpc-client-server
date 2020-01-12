#include <string>
#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "messages.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using demo::ProtoRequest;
using demo::ProtoResponse;
using demo::Greeter;

ProtoRequest MakeRequest() {
    //TODO: implement it
    ProtoRequest request;
    request.set_id(1234);
    request.set_query("who is the laughing man");
    return request;
}

class DemoClient {
    public:
        //constructor
        DemoClient(std::shared_ptr<Channel> channel) : stub_(Greeter::NewStub(channel)) {

        }
    
        void SayHello() {
            std::cout << "client calling SayHello" << std::endl;
            ProtoRequest request;
            ProtoResponse response;
            request = MakeRequest();
            GetResponse(request, &response);
        }
    
    private:
        bool GetResponse(const ProtoRequest& request, ProtoResponse* response) {
            ClientContext context;

            Status status = stub_->SayHello(&context, request, response);

            if(!status.ok()) {
                std::cout << "getting response from SayHello failed" << std::endl;
                return false;
            }

            if(response->id() == 0) {
                std::cout << "response id is not set" << std::endl;
            }

            if(response->values_size() == 0) {
                std::cout << "response values is empty" << std::endl;
            }
            else {
                std::cout << "response values: ";
                for(int i=0; i<response->values_size(); ++i) {

                    std::cout << response->values(0) << " ";
                }
                std::cout << std::endl;
            }

            return true;
        }

        std::unique_ptr<Greeter::Stub> stub_; //client
};

int main(int argc, char** argv) {
    DemoClient client(grpc::CreateChannel("localhost:6666", grpc::InsecureChannelCredentials()));
    std::cout << "Say Hello" << std::endl;
    client.SayHello();
    return 0;
}


