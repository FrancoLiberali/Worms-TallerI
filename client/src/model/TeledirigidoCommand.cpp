#include "TeledirigidoCommand.h"

TeledirigidoCommand::TeledirigidoCommand(int idJugador, int x, int y)
    : idJugador(idJugador), x(x), y(y){}

void TeledirigidoCommand::send(ProxyClient& proxy){
    proxy.sendTeledirigido(x, y);
}