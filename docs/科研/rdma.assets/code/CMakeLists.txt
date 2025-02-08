cmake_minimum_required(VERSION 3.10)
project(RDMA_RC_example)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O2")

add_executable(RDMA_RC_example RDMA_RC_example.c)
target_link_libraries(RDMA_RC_example PRIVATE ibverbs)