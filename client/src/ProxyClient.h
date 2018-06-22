#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>
#include "common/socket.h"
#include "model/Model.h"

class Model;

class ProxyClient {
private:
    Socket socket;
    void sendInt(int num);
    void sendChar(char bye);
    bool open;
    Model* model;
public:
    ProxyClient(Socket socket);
    ~ProxyClient() noexcept;
    void addModel(Model* model);
    void connect(std::string& host, std::string& port);
    void close();
    int receiveInt();
    int receivePosY();
    int receivePosX();
    int receiveAngle();
    char receiveChar();
    int receiveWidht();
    int receiveHeight();
    std::string receiveName();

    void sendName(std::string& msg);
    void sendMapAndPlayers(int idMap, int num);
    void sendMoveWorm(int idPlayer, int dir);
    void sendJump(int id);
    void sendBackJump(int id);
    void sendWeaponSelect(int idPlayer, int idWeapon);
    void sendChangeAim(int idPlayer, int delta);
    void sendChargePower(int idPlayer);
    void sendWormShoot(int idPlayer);
    void sendCountDown(int idPlayer, int time);
    void sendCreateRoom(std::string& nameRoom,int  numPlayer,std::string nameMap);
    void sendJoinRoom(int idRoom);
    void sendTeledirigido(int idPlayer, int x, int y);

};

#endif