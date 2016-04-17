# Project definition
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(PROJECT_NAME handmade-http-server)
set(PROJECT_VERSION "1.0-SNAPSHOT")
project(${PROJECT_NAME} LANGUAGES CXX)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Dependencies
set(BOOST_MIN_VERSION "1.58.0")
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS system)

# Create executable
subdirs(${PROJECT_SOURCE_DIR}/src)
