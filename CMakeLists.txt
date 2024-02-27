cmake_minimum_required(VERSION 3.22)

message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "CMake source directory: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMake binary directory: ${CMAKE_BINARY_DIR}")

set(PROJECT_NAME jsonToBatch)

project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/lib)

set(SOURCES
    src/main.cpp
    lib/easylogging++.cc
)

message(STATUS "Checking for MinGW")
IF (MINGW)
  include_directories(${PROJECT_SOURCE_DIR}/include)
  link_directories(${PROJECT_SOURCE_DIR}/lib)
  message(STATUS "Using MinGW")
ENDIF ()

link_directories(${PROJECT_SOURCE_DIR}/lib)
message(STATUS "Checking for Catch2 library")
find_library(CATCH2 Catch2)
if(NOT CATCH2)
  message(WARNING "catch2 library not found")
endif()

message(STATUS "Checking for jsoncpp library")
find_library(JSONCPP jsoncpp)
if(NOT JSONCPP)
  message(WARNING "jsoncpp library not found")
endif()


message(STATUS "Adding executable ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${SOURCES})

message(STATUS "Linking libraries")
target_link_libraries(${PROJECT_NAME} 
  ${PROJECT_SOURCE_DIR}/oldLib/libCatch2.a 
  ${PROJECT_BINARY_DIR}/lib/jsoncpp/src/lib_json/libjsoncpp.a)

message(STATUS "Adding include directories")
target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

