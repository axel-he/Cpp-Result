cmake_minimum_required(VERSION 3.10)

project(example VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# -----------------------------------------------------------------------------
# Examples
# -----------------------------------------------------------------------------
add_executable(BasicExample examples/BasicExample.cpp)
add_executable(ResultValueExample examples/ResultValueExample.cpp)
add_executable(HandlerExample examples/HandlerExample.cpp)
add_executable(ResultComparison examples/ResultComparison.cpp)
add_executable(TouchResultValue examples/TouchResultValue.cpp)

# set global include directories for project executables
include_directories(src/)
