#ifndef _PRE_GAME_MANAGER_H
#define _PRE_GAME_MANAGER_H

#include "mapwindow.h"
#include "resultwindow.h"
#include "ProxyClient.h"
#include "Room.h"

class mapWindow;
class resultwindow;
class ProxyClient;

/**
* @class PreGameManager
* Manejador de las ventanas antes de que inicie el juego principal
* Hall principal y salas
*/

class PreGameManager {
private:
    ProxyClient& proxy;
    mapWindow* hall;
    resultwindow* result;
public:
    PreGameManager(ProxyClient& proxy);
    ~PreGameManager();
    bool showHall();
    bool showResult();
    void addMap(std::string& nameMap);
    void addRoom(Room* room);
    void setResult(std::string result);
};

#endif