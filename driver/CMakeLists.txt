cmake_minimum_required(VERSION 3.0)
project(xtFireHIDDriver)
set(PROJECT_VERSION 0.1)

message(STATUS "--- Configuration started ------------------")

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD 11)
enable_language(CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug Force)
endif()

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/install/lib" CACHE PATH "Build directory" FORCE)
message(STATUS  "CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/install/bin")
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/install/bin" CACHE PATH "Build directory" FORCE)
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Configuring includes directories
include_directories(
  "./modules/include"
)

set(LIBRARY_NAME ${PROJECT_NAME})
set(SAMPLE_NAME "libtest")
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

  set(LIBRARY_NAME ${LIBRARY_NAME}d)
  set(SAMPLE_NAME ${SAMPLE_NAME}d)
endif()
message(STATUS "LIBRARY_NAME: ${LIBRARY_NAME}")

add_subdirectory("modules")
add_subdirectory("samples")

message("--- Configuration completed! ------------------")
