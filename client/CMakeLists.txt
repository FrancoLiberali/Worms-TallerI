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
	src/controller/WormChangeLifeEvent.cpp
    src/controller/WormWeaponEvent.cpp
	src/controller/CreateVigaEvent.cpp
	src/controller/CreateWormEvent.cpp
	src/controller/PlayerIdEvent.cpp
	src/controller/PlayerConnectEvent.cpp
	src/controller/StartTurnEvent.cpp
	src/controller/PlayerOffEvent

    src/controller/ClientCommandSender.cpp
	src/controller/Controller.cpp

	src/common/Thread.cpp
	src/common/socket.cpp
	src/common/socket_error.cpp
	src/ProxyClient.cpp
	src/GameBuilder.cpp

	src/model/Model.cpp
	src/model/GameControllerProxy.cpp
	src/model/WormMoveCommand.cpp
	src/model/WormJumpCommand.cpp
	src/model/WormWeaponCommand.cpp

	src/view/mainView.cpp
	src/view/SdlException.cpp
	src/view/Escenario.cpp
	src/view/WormView.cpp
	src/view/newView/Boot.cpp
	src/view/newView/SdlException.cpp
	src/view/newView/SdlScreen.cpp
	src/view/newView/Sprite.cpp
	src/view/newView/SpriteConfigurator.cpp
	src/view/newView/TextureManager.cpp
	src/view/newView/TextManager.cpp
	src/view/newView/TextView.cpp
	src/view/MenuWeaponView.cpp
	src/view/Weapon.cpp
	src/view/Shape.cpp
	src/view/VigaView.cpp
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
install(FILES assets/Login_Menu3.glade DESTINATION ${CMAKE_BINARY_DIR})
install(FILES test/socket.txt DESTINATION ${CMAKE_BINARY_DIR})

#gtkmm-3.0
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -I/usr/include/gtkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gtkmm-3.0/include -I/usr/include/atkmm-1.6 -I/usr/include/giomm-2.4 -I/usr/lib/x86_64-linux-gnu/giomm-2.4/include -I/usr/include/pangomm-1.4 -I/usr/lib/x86_64-linux-gnu/pangomm-1.4/include -I/usr/include/gtk-3.0 -I/usr/include/cairomm-1.0 -I/usr/lib/x86_64-linux-gnu/cairomm-1.0/include -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/gtk-3.0/unix-print -I/usr/include/gdkmm-3.0 -I/usr/lib/x86_64-linux-gnu/gdkmm-3.0/include -I/usr/include/atk-1.0 -I/usr/include/glibmm-2.4 -I/usr/lib/x86_64-linux-gnu/glibmm-2.4/include -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/sigc++-2.0 -I/usr/lib/x86_64-linux-gnu/sigc++-2.0/include -I/usr/include/pango-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/freetype2 -I/usr/include/libpng12 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/harfbuzz -lgtkmm-3.0 -latkmm-1.6 -lgdkmm-3.0 -lgiomm-2.4 -lpangomm-1.4 -lgtk-3 -lglibmm-2.4 -lcairomm-1.0 -lgdk-3 -latk-1.0 -lgio-2.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo-gobject -lpango-1.0 -lcairo -lsigc-2.0 -lgobject-2.0 -lglib-2.0")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
pkg_check_modules(GTKMM gtkmm-3.0)

include_directories(${GTK3_INCLUDE_DIRS}
        ${GTKMM_INCLUDE_DIRS})

link_directories(${GTK3_LIBRARY_DIRS}
        ${GTKMM_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})


find_package(PkgConfig REQUIRED)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)

target_link_libraries(client alllib SDL2 SDL2_image SDL2_mixer ${GTK3_LIBRARIES} ${GTKMM_LIBRARIES})
