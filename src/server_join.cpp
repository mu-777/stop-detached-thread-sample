#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

#include "threadctrl.pb.h"
#include "threadctrl.grpc.pb.h"

namespace threadctrl {
class ThreadControlImpl_join final : public ThreadControl::Service {
  std::atomic_bool _isRunning;
  std::vector<std::thread> _workingThreads;

public:
  ThreadControlImpl_join() : ThreadControl::Service(), _isRunning(true) {
    std::cout << "Constructor" << std::endl;
  }

  ::grpc::Status RunThread(::grpc::ServerContext* context, const RunThreadReq* req,
                           RunThreadResp* res) override {
    std::cout << "RunThread: " << req->key() << std::endl;
    std::thread th([&](std::string str) -> void{
      std::cout << "Start Thread: " << str << std::endl;
      auto cnt = 0;
      auto tid = std::this_thread::get_id();
      while (_isRunning.load() && cnt < 10) {
        std::cout << str << "[" << tid << "]: " << cnt++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
      }
      std::cout << "Finish Thread[" << tid << "]: " << str << std::endl;
    }, req->key());
    _workingThreads.push_back(std::move(th));
    return ::grpc::Status::OK;
  }

  ::grpc::Status StopAllThread(::grpc::ServerContext* context, const StopAllThreadReq* req,
                               StopAllThreadResp* res) override {
    std::cout << "StopAllThread" << std::endl;
    _isRunning.store(false);
    for (auto& th : _workingThreads) {
      if (th.joinable()) {
        th.join();
      }
    }
    std::cout << "Stopped" << std::endl;
    _isRunning.store(true);
    _workingThreads.clear();
    return ::grpc::Status::OK;
  }
};
};

void RunServer() {
  std::string server_address("localhost:50051");
  threadctrl::ThreadControlImpl_join threadctrl;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&threadctrl);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  std::cout << "RunServer" << std::endl;
  RunServer();
  return 0;
}

