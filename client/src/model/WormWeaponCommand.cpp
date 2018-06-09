#include "WormWeaponCommand.h"

WormWeaponCommand::WormWeaponCommand(int idJugador, const int idWeapon)
    :idJugador(idJugador), idWeapon(idWeapon){}
    
void WormWeaponCommand::send(ProxyClient& proxy){
    proxy.sendChar(4);
    proxy.sendInt(idJugador);
    proxy.sendInt(idWeapon);
}