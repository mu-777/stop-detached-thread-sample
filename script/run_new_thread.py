import sys
import grpc
from threadctrl_pb2 import RunThreadReq, RunThreadResp
from threadctrl_pb2_grpc import ThreadControlStub


# ----------------------------------------
if __name__ == '__main__':
  channel = grpc.insecure_channel('localhost:50051')
  stub = ThreadControlStub(channel)
  req = RunThreadReq(key="0" if len(sys.argv) == 0 else sys.argv[1])
  res = stub.RunThread(req)
  print(res)