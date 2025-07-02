cmake_minimum_required(VERSION 3.14)
project(pose_module LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dynamically find pybind11 from pip install
execute_process(
    COMMAND python3 -m pybind11 --cmakedir
    OUTPUT_VARIABLE PYBIND11_CMAKE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

list(APPEND CMAKE_PREFIX_PATH ${PYBIND11_CMAKE_DIR})

find_package(pybind11 REQUIRED)

pybind11_add_module(pose_module pose_module.cpp)
