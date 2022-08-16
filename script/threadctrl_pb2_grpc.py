# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import threadctrl_pb2 as threadctrl__pb2


class ThreadControlStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.RunThread = channel.unary_unary(
                '/threadctrl.ThreadControl/RunThread',
                request_serializer=threadctrl__pb2.RunThreadReq.SerializeToString,
                response_deserializer=threadctrl__pb2.RunThreadResp.FromString,
                )
        self.StopAllThread = channel.unary_unary(
                '/threadctrl.ThreadControl/StopAllThread',
                request_serializer=threadctrl__pb2.StopAllThreadReq.SerializeToString,
                response_deserializer=threadctrl__pb2.StopAllThreadResp.FromString,
                )


class ThreadControlServicer(object):
    """Missing associated documentation comment in .proto file."""

    def RunThread(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def StopAllThread(self, request, context):
        """Missing associated documentation comment in .proto file."""
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_ThreadControlServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'RunThread': grpc.unary_unary_rpc_method_handler(
                    servicer.RunThread,
                    request_deserializer=threadctrl__pb2.RunThreadReq.FromString,
                    response_serializer=threadctrl__pb2.RunThreadResp.SerializeToString,
            ),
            'StopAllThread': grpc.unary_unary_rpc_method_handler(
                    servicer.StopAllThread,
                    request_deserializer=threadctrl__pb2.StopAllThreadReq.FromString,
                    response_serializer=threadctrl__pb2.StopAllThreadResp.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'threadctrl.ThreadControl', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class ThreadControl(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def RunThread(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/threadctrl.ThreadControl/RunThread',
            threadctrl__pb2.RunThreadReq.SerializeToString,
            threadctrl__pb2.RunThreadResp.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def StopAllThread(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/threadctrl.ThreadControl/StopAllThread',
            threadctrl__pb2.StopAllThreadReq.SerializeToString,
            threadctrl__pb2.StopAllThreadResp.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)
