cmake_minimum_required(VERSION 3.16)
project(pico-dev)

include(ExternalProject)

ExternalProject_Add(binary
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/source
    INSTALL_COMMAND true
)

ExternalProject_Add(utest
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/test
    INSTALL_COMMAND true
)
