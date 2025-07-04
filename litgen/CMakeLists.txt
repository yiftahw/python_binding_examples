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

# Find a Python3 interpreter
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# run the litgen script to generate bindings
add_custom_target(generate_bindings
    ALL
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/gen_bindings.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating C++ bindings using litgen"
)

set(MODULE_NAME "geometry2d")
project(${MODULE_NAME} CXX)

# Create a pybind11 module from the generated C++ file
pybind11_add_module(${MODULE_NAME}
    ${CMAKE_SOURCE_DIR}/${MODULE_NAME}.cpp
)
add_dependencies(${MODULE_NAME} generate_bindings)

# Ignore the machine, os, compiler suffixes in the output name
# This is fine for local development
set_target_properties(${MODULE_NAME} PROPERTIES
    PREFIX ""
    SUFFIX ".so"
    OUTPUT_NAME "${MODULE_NAME}"
)

add_custom_target(copy_shared_lib
    ALL
    DEPENDS ${MODULE_NAME}
    COMMENT "Copying '.so' file to the output directory"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/${MODULE_NAME}.so" "${CMAKE_SOURCE_DIR}/${MODULE_NAME}.so"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    VERBATIM
)
