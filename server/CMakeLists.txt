cmake_minimum_required(VERSION 2.8.11)

project(box2d-example)

set (CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE BOX2D_FILES ${PROJECT_SOURCE_DIR}/Box2D/*.cpp)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

find_package( Threads )

add_executable(tp main.cpp ${SRC_FILES} ${BOX2D_FILES})

target_link_libraries( tp ${CMAKE_THREAD_LIBS_INIT} )


