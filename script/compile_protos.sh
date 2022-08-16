#!/usr/bin/env bash
REPODIR=$(cd $(dirname $0);cd ..;pwd)
PROTO_ROOT=$REPODIR/protos
OUTPUT_DIR=$REPODIR/script

python3 -m grpc_tools.protoc \
  --proto_path=$PROTO_ROOT \
  --python_out=$OUTPUT_DIR \
  --grpc_python_out=$OUTPUT_DIR \
  $PROTO_ROOT/*.proto
