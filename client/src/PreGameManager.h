#ifndef _PRE_GAME_MANAGER_H
#define _PRE_GAME_MANAGER_H

#include "mapwindow.h"
#include "ProxyClient.h"
#include "Room.h"

class mapWindow;
class ProxyClient;

/**
* @class PreGameManager
* Manejador de las ventanas antes de que inicie el juego principal
* Hall principal y salas de espera
*/

class PreGameManager {
private:
    ProxyClient& proxy;
    mapWindow* hall;
public:
    PreGameManager(ProxyClient& proxy);
    void showHall();
    void addMap(std::string nameMap);
    void addRoom(Room* room);
};

#endif