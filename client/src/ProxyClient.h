#ifndef _PROXY_CLIENT_H
#define _PROXY_CLIENT_H

#include <string>
#include "common/socket.h"

class ProxyClient {
private:
    Socket socket;
    void sendInt(int num);
    void sendChar(char bye);
public:
    ProxyClient(Socket socket);
    ~ProxyClient() noexcept;
    void close();
    int receiveInt();
    int receivePos();
    int receiveAngle();
    char receiveChar();
    std::string receiveName();
    void sendName(int id, std::string& msg);
    void sendMapAndPlayers(int idMap, int num);
    void sendMoveWorm(int idPlayer, int dir);
    void sendJump(int dir, int id);
    void sendWeaponSelect(int idPlayer, int idWeapon);
    void sendChangeAim(int idPlayer, int delta);
};

#endif