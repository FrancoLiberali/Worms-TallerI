cmake_minimum_required(VERSION 2.8)

project(worms_client)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_library(controllerlib
	src/controller/ClientEventReceiver.cpp
    src/controller/EventHandler.cpp
)

add_library(commonlib
	src/common/Thread.cpp
	src/common/Queue.cpp
)

add_library(viewlib
	src/view/View.cpp
	src/view/Window.cpp
	src/view/SdlException.cpp
	src/view/Escenario.cpp
	src/view/Texture.cpp
)

message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (client
	src/clientMain.cpp
)

target_link_libraries(client viewlib commonlib controllerlib SDL2 SDL2_image)
install(FILES assets/agua.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/vigah.png DESTINATION ${CMAKE_BINARY_DIR})
