#ifndef _WORM_WEAPON_COMMAND_H
#define _WORM_WEAPON_COMMAND_H

#include "ClientCommand.h"

class WormWeaponCommand : public ClientCommand{
private:
    int idJugador;
    int idWeapon;
public:
    WormWeaponCommand(int idJugador, const int idWeapon);
    void send(ProxyClient& proxy);
};

#endif