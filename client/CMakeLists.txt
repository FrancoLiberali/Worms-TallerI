cmake_minimum_required(VERSION 3.5)
PROJECT(worms-client CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/src)

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
    ui/mapwindow.ui
	ui/mainwindow.ui
	ui/resultwindow.ui
)

# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

# Agrego los recursos.
qt5_add_resources(RESOURCES src/recursos.qrc)

add_executable(worms-client
	src/mainClient.cpp
	src/ProxyClient.cpp
	src/GameClient.cpp

	src/mapwindow.cpp
	src/mainwindow.cpp
	src/resultwindow.cpp
	src/PreGameManager.cpp
	src/Room.cpp

	src/controller/ClientCommandSender.cpp
	src/controller/ClientEventReceiver.cpp
	src/controller/Controller.cpp
	src/controller/EventFactory.cpp
	src/controller/EventHandler.cpp
	src/controller/MouseState.cpp
	src/controller/event/Event.cpp
	src/controller/event/WormMoveEvent.cpp
	src/controller/event/WormChangeStateEvent.cpp
	src/controller/event/WormChangeLifeEvent.cpp
	src/controller/event/WormWeaponEvent.cpp
	src/controller/event/CreateVigaEvent.cpp
	src/controller/event/CreateWormEvent.cpp
	src/controller/event/CreateMissileEvent.cpp
	src/controller/event/CreateStageEvent.cpp
	src/controller/event/MissileMoveEvent.cpp
	src/controller/event/MissileExploteEvent.cpp
	src/controller/event/PlayerLoseEvent.cpp
	src/controller/event/BackgroundEvent.cpp
	src/controller/event/WormChangeAimEvent.cpp
	src/controller/event/StartTurnEvent.cpp
	src/controller/event/PlayerOffEvent.cpp
	src/controller/event/GameWinnerEvent.cpp
	src/controller/event/WeaponDoneEvent.cpp
	src/controller/event/CameraMoveEvent.cpp
	src/controller/event/RightTargertEvent.cpp
	src/controller/event/SecondEvent.cpp
	src/controller/event/WindChangedEvent.cpp

	src/common/Thread.cpp
	src/common/socket.cpp
	src/common/Util.cpp

	src/model/Model.cpp
	src/model/GameControllerProxy.cpp
	src/model/command/WormMoveCommand.cpp
	src/model/command/WormJumpCommand.cpp
	src/model/command/WormWeaponCommand.cpp
	src/model/command/ChangeAimCommand.cpp
	src/model/command/WormShootCommand.cpp
	src/model/command/ChargePowerCommand.cpp
	src/model/command/ChangeCountDownCommand.cpp
	src/model/command/TeledirigidoCommand.cpp
	src/model/command/LeaveRoomCommand.cpp

	src/view/mainView.cpp
	src/view/Escenario.cpp
	src/view/WormView.cpp
	src/view/
	src/view/SdlScreen.cpp
	src/view/Sprite.cpp

	src/view/TextView.cpp
	src/view/MenuWeaponView.cpp
	src/view/Weapon.cpp
	src/view/Shape.cpp
	src/view/VigaView.cpp
	src/view/AimView.cpp
	src/view/Camera.cpp
	src/view/bullets/BulletFactory.cpp
	src/view/bullets/BulletView.cpp
	src/view/bullets/BazookaView.cpp
	src/view/bullets/MortarView.cpp
	src/view/bullets/FragmentView.cpp
	src/view/bullets/GreenGrenadeView.cpp
	src/view/bullets/RedGrenadeView.cpp
	src/view/bullets/BananaView.cpp
	src/view/bullets/HolyView.cpp
	src/view/bullets/DynamiteView.cpp
	src/view/bullets/AirMissileView.cpp
	src/view/PowerView.cpp
	src/view/PanelInfo.cpp
	src/view/WatchView.cpp

	src/manager/Boot.cpp
	src/manager/FontManager.cpp
	src/manager/TextureManager.cpp
	src/manager/TextManager.cpp
	src/manager/SoundManager.cpp
	src/manager/SpriteConfigurator.cpp

	src/exception/GameException.cpp
	src/exception/SdlException.cpp
	src/exception/socket_error.cpp

	${UIS_HEADERS}
)




#busca que las librerias necesarias se encuentren instaldas
find_package(PkgConfig REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# Use the Widgets module from Qt 5.
target_link_libraries(worms-client Qt5::Widgets)

#Agrego las librearias de SDL2
target_link_libraries(worms-client SDL2 SDL2_image SDL2_mixer SDL2_ttf)

# Definiendo la dirección de instalacicón `cmake .. -DINSTALL_PATH=<dir>`
if(NOT INSTALL_PATH)
  set(INSTALL_PATH "/usr/local")
endif(NOT INSTALL_PATH)

# El primero es el template, el segundo es el destino
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_SOURCE_DIR}/config.h"
)

# Copio la carpeta de recursos al directorio de instalación.
install(DIRECTORY resource DESTINATION ${INSTALL_PATH})
