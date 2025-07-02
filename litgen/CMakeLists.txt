cmake_minimum_required(VERSION 3.16)
project(point_litgen_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Fetch pybind11
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG        v2.11.0
)
FetchContent_MakeAvailable(pybind11)

# Create a pybind11 module from the generated C++ file
pybind11_add_module(pose_module
    ${CMAKE_SOURCE_DIR}/pose_module_api.cpp
)

# This helps Pybind11 produce the correct symbol name for Python
set_target_properties(pose_module PROPERTIES
    PREFIX ""
    OUTPUT_NAME "pose_module"
)
