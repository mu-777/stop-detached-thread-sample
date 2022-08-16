#!/usr/bin/env bash
pushd $(dirname $0)/../

CTR_NAME=grpc_dev

docker run \
  -d --rm --cap-add sys_ptrace \
  -v /etc/group:/etc/group:ro \
  -v /etc/passwd:/etc/passwd:ro \
  -v /etc/shadow:/etc/shadow:ro \
  -v $HOME/.vscode-server:$HOME/.vscode-server \
  -u $(id -u $USER):$(id -g $USER) \
  -v $PWD:$PWD \
  --name $CTR_NAME mu-777/grpc-cpp-dev 

popd