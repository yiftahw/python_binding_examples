include(CMakePrintHelpers)
cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
###############################################################
# Project
###############################################################
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(pose_module LANGUAGES CXX)

###############################################################
# CMake setup
###############################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

###############################################################
# Boost Python
###############################################################
find_package(Boost 1.79.0 REQUIRED COMPONENTS python310)
include_directories(${Boost_INCLUDE_DIR}/)
find_package(Python 3.10 COMPONENTS Interpreter Development)
include_directories(${Python_INCLUDE_DIRS})

set(PROJECT_FILES
        pose_module.cpp
)

###############################################################
# Set executable and target link libraries
###############################################################
add_definitions(-DGLFW_INCLUDE_NONE -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")

set(COMMON_LIB_DIRECTORIES
        ${Boost_LIBRARY_DIRS}
        ${Python_LIBRARY_DIRS}
)

set(COMMON_LIBS
        boost_python310
        python3.10
)

add_library(pose_module SHARED ${PROJECT_FILES})
target_link_directories(pose_module PRIVATE ${COMMON_LIB_DIRECTORIES})
target_link_libraries(pose_module ${COMMON_LIBS})

# Set output directory for shared library one directory up
set_target_properties(pose_module PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

###############################################################
# POST BUILD
# Create a `.pyi` stub with `stubgen`
# Requires `mypy` to be installed
###############################################################
# check if `stubgen` is available
find_program(STUBGEN_EXECUTABLE NAMES stubgen)
if(NOT STUBGEN_EXECUTABLE)
        message(FATAL_ERROR "stubgen not found. Please run 'pip install mypy' to generate .pyi stub files.")
endif()

add_custom_command(TARGET pose_module POST_BUILD
        COMMENT "Copying '.so' file to the output directory"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/libpose_module.so" "${CMAKE_SOURCE_DIR}/libpose_module.so"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        VERBATIM
)

add_custom_target(gen_stub
        COMMAND ${STUBGEN_EXECUTABLE} --include-docstrings -o . -m libpose_module
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/libpose_module.pyi" "${CMAKE_SOURCE_DIR}/libpose_module.pyi"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
        VERBATIM
)