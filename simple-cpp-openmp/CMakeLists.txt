cmake_minimum_required(VERSION 3.5)
cmake_policy(VERSION 3.5...3.27)

set(ProjectName simple-cpp-openmp)
project(${ProjectName} LANGUAGES CXX)

find_package(hip REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(${ProjectName} main.cpp)
target_compile_options(${ProjectName} PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(${ProjectName} PRIVATE hip::device ${OpenMP_CXX_FLAGS})
