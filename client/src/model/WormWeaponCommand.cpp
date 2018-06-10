#include "WormWeaponCommand.h"

WormWeaponCommand::WormWeaponCommand(int idJugador, const int idWeapon)
    :idJugador(idJugador), idWeapon(idWeapon){}
    
void WormWeaponCommand::send(ProxyClient& proxy){
    proxy.sendWeaponSelect(idJugador, idWeapon);
}