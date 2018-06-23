#include "TeledirigidoCommand.h"

TeledirigidoCommand::TeledirigidoCommand(int idPlayer, int x, int y)
    : idPlayer(idPlayer), x(x), y(y){}

void TeledirigidoCommand::send(ProxyClient& proxy){
    proxy.sendTeledirigido(idPlayer, x, y);
}