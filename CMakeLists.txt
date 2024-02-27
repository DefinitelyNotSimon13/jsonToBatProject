cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME jsonToBatch)

project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/main.cpp
    lib/easylogging++.cc
)

IF (MINGW)
  include_directories(${PROJECT_SOURCE_DIR}/include)
  link_directories(${PROJECT_SOURCE_DIR}/lib)
  message(STATUS "Using MinGW")
ENDIF ()


find_library(CATCH2 Catch2)
if(NOT CATCH2)
  message(FATAL_ERROR "catch2 library not found")
endif()

find_library(JSONCPP jsoncpp)
if(NOT JSONCPP)
  message(FATAL_ERROR "jsoncpp library not found")
endif()

#include_directories(${PROJECT_SOURCE_DIR}/include)

#link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Catch2 jsoncpp)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

