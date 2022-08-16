#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

#include "threadctrl.pb.h"
#include "threadctrl.grpc.pb.h"

namespace threadctrl {
class ThreadControlImpl final : public ThreadControl::Service {
  std::atomic_bool _isRunning;
  std::atomic_uint _workingThreads;
  std::mutex _threadsMutex;
  std::condition_variable _threadsCond;

public:
  ThreadControlImpl() : ThreadControl::Service(), _isRunning(true), _workingThreads(0) {
    std::cout << "Constructor" << std::endl;
  }

  ::grpc::Status RunThread(::grpc::ServerContext* context, const RunThreadReq* req,
                           RunThreadResp* res) override {
    std::cout << "RunThread: " << req->key() << std::endl;
    std::thread th([&](std::string str) -> void{
      std::cout << "Start Thread: " << str << std::endl;
      auto cnt = 0;
      auto tid = std::this_thread::get_id();
      while (_isRunning.load()) {
        std::cout << str << "[" << tid << "]: " << cnt++ << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
      }
      --_workingThreads;
      std::cout << "Finish Thread[" << tid << "]: " << str << std::endl;
      _threadsCond.notify_one();
    }, req->key());
    ++_workingThreads;
    th.detach();
    return ::grpc::Status::OK;
  }

  ::grpc::Status StopAllThread(::grpc::ServerContext* context, const StopAllThreadReq* req,
                               StopAllThreadResp* res) override {
    std::cout << "StopAllThread" << std::endl;
    _isRunning.store(false);
    std::unique_lock<std::mutex> l(_threadsMutex);
    _threadsCond.wait(l, [&]{return _workingThreads == 0;});
    std::cout << "Stopped" << std::endl;
    _isRunning.store(true);
    return ::grpc::Status::OK;
  }
};
};

void RunServer() {
  std::string server_address("localhost:50051");
  threadctrl::ThreadControlImpl threadctrl;

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

