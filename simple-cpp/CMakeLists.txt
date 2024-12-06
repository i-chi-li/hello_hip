cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5...3.27)

set(ProjectName simple-cpp)
project(${ProjectName} LANGUAGES CXX)

find_package(hip REQUIRED)

add_executable(${ProjectName} main.cpp)
target_link_libraries(${ProjectName} PRIVATE hip::device)
