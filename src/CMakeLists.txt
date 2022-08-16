
include_directories(${Protobuf_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

pb_grpc_generate_cpp(PROTO_SRCS PROTO_HDRS GRPC_SRCS GRPC_HDRS
        ${CMAKE_SOURCE_DIR}/protos/threadctrl.proto
        )

add_library(grpc_proto STATIC ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS})
target_link_libraries(grpc_proto gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf)

set(SERVER_TARGET server)
add_executable(${SERVER_TARGET} "${SERVER_TARGET}.cpp")
target_link_libraries(${SERVER_TARGET} grpc_proto)
install(TARGETS ${SERVER_TARGET} RUNTIME DESTINATION bin)
