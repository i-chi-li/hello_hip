cmake_minimum_required(VERSION 3.21)
cmake_policy(VERSION 3.21.3...3.27)

if (WIN32)
    list(APPEND CMAKE_PREFIX_PATH $ENV{HIP_PATH})
else ()
    list(APPEND CMAKE_PREFIX_PATH /opt/rocm)
endif ()
set(HIP_PLATFORM amd)
#set(GPU_TARGETS "gfx1036")
#set(GPU_TARGETS "gfx803;gfx900;gfx1036")

project(hello_hip)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(simple-cpp)
add_subdirectory(simple-cpp-openmp)
add_subdirectory(simple-hip)
