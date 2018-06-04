cmake_minimum_required(VERSION 2.8)

project(worms_client)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_library(alllib
	src/controller/ClientEventReceiver.cpp
    src/controller/EventHandler.cpp
    src/controller/Event.cpp
    src/controller/EventFactory.cpp
    src/controller/WormMoveEvent.cpp
    src/controller/WormChangeStateEvent.cpp
    src/controller/ClientCommandSender.cpp
	src/controller/Controller.cpp
	src/common/Thread.cpp
	src/ProxyClient.cpp
	src/model/Model.cpp
	src/model/GameControllerProxy.cpp
	src/model/WormMoveCommand.cpp
	src/view/View.cpp
	src/view/Window.cpp
	src/view/SdlException.cpp
	src/view/Escenario.cpp
	src/view/Texture.cpp
	src/view/Animation.cpp
	src/view/WormView.cpp
)


message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

add_executable (client
	src/clientMain.cpp
)

target_link_libraries(client alllib SDL2 SDL2_image)
install(FILES assets/agua.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/vigah.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES assets/wwalk.png DESTINATION ${CMAKE_BINARY_DIR})
install(FILES test/socket.txt DESTINATION ${CMAKE_BINARY_DIR})
