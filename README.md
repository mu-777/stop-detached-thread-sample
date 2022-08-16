# Sample to stop detached thread

## Setup
1. Build docker images
    - ```
      bash docker/docker-build.sh
      ```
1. Run docker container
    - ```
      bash docker/docker-run.sh
      ```

## How to use
1. Enter the container
    - ```
      docker exec -it grpc_dev bash
      ```
1. Build server
    - ```
      cd <this_repo>
      mkdir -p build; cd build; cmake ..; make -j8
      ```
1. Compile grpc for python scripts
    - ```
      cd <this_repo>/script
      bash compile_protos.sh 
      ```
1. Run server
    - ```
      ./build/src/server
      ```
1. Add thread
    - ```
      cd <this_repo>/script
      python3 run_new_thread.py <any string>
      ```
1. Stop threads
    - ```
      cd <this_repo>/script
      python3 stop_all_threads.py
      ```

## How to dev
1. Connect to sources in the container with vscode
    - Open the project in vscode with Remote-WSL mode
    - Open the project in vscode with Remote-Container via Remote-WSL vscode
