#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>
#include "common/socket.h"

class ProxyClient {
private:
    Socket socket;
    void sendInt(int num);
    void sendChar(char bye);
    bool open;
public:
    ProxyClient(Socket socket);
    ~ProxyClient() noexcept;
    void close();
    int receiveInt();
    int receivePosY();
    int receivePosX();
    int receiveAngle();
    char receiveChar();
    std::string receiveName();

    void sendName(int id, std::string& msg);
    void sendMapAndPlayers(int idMap, int num);
    void sendMoveWorm(int idPlayer, int dir);
    void sendJump(int id);
    void sendBackJump(int id);
    void sendWeaponSelect(int idPlayer, int idWeapon);
    void sendChangeAim(int idPlayer, int delta);
    void sendChargePower(int idPlayer);
    void sendWormShoot(int idPlayer);
    void sendCountDown(int idPlayer, int time);
};

#endif