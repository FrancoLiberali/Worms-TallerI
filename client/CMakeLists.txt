cmake_minimum_required(VERSION 3.5)
PROJECT(worm_client CXX)

#set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

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

add_executable(client
	src/main.cpp
	src/mapwindow.cpp
	src/namewindow.cpp
	src/connectwindow.cpp
	src/mainwindow.cpp

	src/controller/ClientEventReceiver.cpp
	src/controller/EventHandler.cpp
	src/controller/Event.cpp
	src/controller/EventFactory.cpp
	src/controller/WormMoveEvent.cpp
	src/controller/WormChangeStateEvent.cpp
	src/controller/WormChangeLifeEvent.cpp
	src/controller/WormWeaponEvent.cpp
	src/controller/CreateVigaEvent.cpp
	src/controller/CreateWormEvent.cpp
	src/controller/CreateMissileEvent.cpp
	src/controller/CreateStageEvent.cpp
	src/controller/MissileMoveEvent.cpp
	src/controller/MissileExploteEvent.cpp
	src/controller/PlayerIdEvent.cpp
	src/controller/PlayerConnectEvent.cpp
	src/controller/WormChangeAimEvent.cpp
	src/controller/StartTurnEvent.cpp
	src/controller/PlayerOffEvent.cpp
	src/controller/GameWinnerEvent.cpp
	src/controller/MouseState.cpp
	src/controller/CameraMove.cpp
	src/controller/ClientCommandSender.cpp
	src/controller/Controller.cpp

	src/common/Thread.cpp
	src/common/socket.cpp
	src/common/socket_error.cpp
	src/ProxyClient.cpp
	src/GameClient.cpp
	src/PreGameManager.cpp

	src/model/Model.cpp
	src/model/GameControllerProxy.cpp
	src/model/WormMoveCommand.cpp
	src/model/WormJumpCommand.cpp
	src/model/WormWeaponCommand.cpp
	src/model/ChangeAimCommand.cpp
	src/model/WormShootCommand.cpp
	src/model/ChargePowerCommand.cpp
	src/model/ChangeCountDownCommand.cpp

	src/view/mainView.cpp
	src/view/SdlException.cpp
	src/view/Escenario.cpp
	src/view/WormView.cpp
	src/view/Boot.cpp
	src/view/SdlException.cpp
	src/view/SdlScreen.cpp
	src/view/Sprite.cpp
	src/view/SpriteConfigurator.cpp
	src/view/TextureManager.cpp
	src/view/TextManager.cpp
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
	src/view/PowerView.cpp

	src/sound/SoundManager.cpp

  ${UIS_HEADERS}


)

find_package(PkgConfig REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

# Use the Widgets module from Qt 5.
target_link_libraries(client Qt5::Widgets SDL2 SDL2_image SDL2_mixer)

