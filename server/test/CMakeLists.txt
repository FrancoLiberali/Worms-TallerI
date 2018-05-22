cmake_minimum_required(VERSION 2.8.11)

project(test)

set (CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR}/.. ${PROJECT_SOURCE_DIR}/../src $"../lib/cxxtest-4.4")

file(GLOB_RECURSE BOX2D_FILES ${PROJECT_SOURCE_DIR}/../Box2D/*.cpp)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/../src/*.cpp)

add_executable(runner runner.cpp ${SRC_FILES} ${BOX2D_FILES})


