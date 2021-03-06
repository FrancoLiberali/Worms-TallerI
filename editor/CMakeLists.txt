cmake_minimum_required(VERSION 3.5)
PROJECT(worms-editor CXX)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(yaml-cpp)

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
		ui/configarmas.ui
        ui/mainwindow.ui
        ui/configgusanos.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Agrego los recursos.
qt5_add_resources(RESOURCES src/recursos.qrc)

add_executable(worms-editor
  src/configarmas.cpp
  src/configgusanos.cpp
  src/conversor.cpp
  src/gusano.cpp
  src/arma.cpp
  src/viga.cpp
  src/vigachica.cpp
  src/vigagrande.cpp
  src/mainwindow.cpp
  src/yamlparser.cpp
  src/registro.cpp
  src/validadordemapa.cpp
  src/main.cpp
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(worms-editor Qt5::Widgets)
# Use the Widgets module from YAML.
target_link_libraries(worms-editor yaml-cpp)

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
install(DIRECTORY recursos DESTINATION ${INSTALL_PATH})

