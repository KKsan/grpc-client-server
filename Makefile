
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
			-pthread\
			-lgrpc++_reflection\
			-ldl

PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = protos

demo_client: messages.pb.o messages.grpc.pb.o demo_client.o 
	$(CXX) $^ $(LDFLAGS) -o $@
demo_server: messages.pb.o messages.grpc.pb.o demo_server.o 
	$(CXX) $^ $(LDFLAGS) -o $@

%.grpc.pb.cc: $(PROTOS_PATH)/messages.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

%.pb.cc: $(PROTOS_PATH)/messages.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

clean:
	rm -f *.o *.pb.cc *.pb.h demo_client demo_server

