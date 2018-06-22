#include "TeledirigidoCommand.h"

TeledirigidoCommand::TeledirigidoCommand(int x, int y)
    : x(x), y(y){}

void TeledirigidoCommand::send(ProxyClient& proxy){
    proxy.sendTeledirigido(x, y);
}