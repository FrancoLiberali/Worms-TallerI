cmake_minimum_required(VERSION 2.8.11)

project(WORMS-SERVER)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/src)

file(GLOB_RECURSE BOX2D_FILES ${PROJECT_SOURCE_DIR}/Box2D/*.cpp)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

find_package( Threads )
find_package(yaml-cpp)

add_executable(worms-server main.cpp ${SRC_FILES} ${BOX2D_FILES})

target_link_libraries(worms-server yaml-cpp)
target_link_libraries( worms-server ${CMAKE_THREAD_LIBS_INIT} )
# Use the Widgets module from YAML.

# Puedo definir funciones desde la linea de comando ejecutando `cmake .. -DINSTALL_PATH=<dir>`
if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)


# El primero es el template, el segundo es el destino
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

# Copio la carpeta de recursos al directorio de instalación.
install(DIRECTORY maps DESTINATION ${INSTALL_PATH})








