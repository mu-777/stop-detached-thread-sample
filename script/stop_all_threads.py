import sys
import grpc
from threadctrl_pb2 import StopAllThreadReq, StopAllThreadResp
from threadctrl_pb2_grpc import ThreadControlStub

# ----------------------------------------
if __name__ == '__main__':
  channel = grpc.insecure_channel('localhost:50051')
  stub = ThreadControlStub(channel)
  req = StopAllThreadReq()
  res = stub.StopAllThread(req)
  print(res)