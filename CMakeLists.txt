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

set(SOURCES
    src/main.cpp
)

option(PRECOMPILED "Wether or not to use the precompiled versions of the libraries" OFF)



message(STATUS "Adding executable ${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${SOURCES})

IF (PRECOMPILED)
  message(STATUS "Using precompiled libraries")
  target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/compiled/libjsoncpp.a
    ${PROJECT_SOURCE_DIR}/lib/compiled/libeasyloggingpp.a
    ${PROJECT_SOURCE_DIR}/lib/compiled/libCatch2Maind.a
  )
ELSE ()
  message(STATUS "Building libraries from source")
  message(STATUS "Adding subdirectories")
  add_subdirectory(lib)
  add_dependencies(${PROJECT_NAME} jsoncpp_static easyloggingpp Catch2::Catch2WithMain)
  message(STATUS "Linking libraries")
  target_link_libraries(${PROJECT_NAME} PRIVATE
    jsoncpp_static
    easyloggingpp
    Catch2::Catch2WithMain
  )
ENDIF()


message(STATUS "Adding include directories")

target_include_directories(${PROJECT_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)
