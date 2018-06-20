cmake_minimum_required(VERSION 3.5)
PROJECT(editor CXX)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej3/include a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR}/src)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
	ui/namewindow.ui
        ui/connectwindow.ui
        ui/mapwindow.ui
	ui/mainwindow.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Agrego los recursos.
qt5_add_resources(RESOURCES src/recursos.qrc)

add_executable(example
  src/mapwindow.cpp
  src/namewindow.cpp
  src/connectwindow.cpp
  src/mainwindow.cpp
  src/main.cpp
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(example Qt5::Widgets)

