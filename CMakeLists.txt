cmake_minimum_required(VERSION 3.10)
project(ChatServer)

# C++ 标准设置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 编译选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pthread")

# 输出目录设置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_OBJECT_DIRECTORY ${CMAKE_BINARY_DIR}/obj)

# 添加头文件搜索路径
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add utils subdirectory to build utils library and test executable
add_subdirectory(utils)

# 创建 server 可执行文件
add_executable(server src/server.cpp src/InetAddress.cc)

# 创建 client 可执行文件
add_executable(client src/client.cpp src/InetAddress.cc)

# 链接选项（如果需要）
target_link_libraries(server pthread)
target_link_libraries(client pthread)
