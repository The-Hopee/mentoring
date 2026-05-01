cmake_minimum_required(VERSION 3.10)
project(math_lib)

add_library(math INTERFACE)

target_include_directories(math
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
