#ifndef _TELEDIRIGO_COMMAND_H
#define _TELEDIRIGO_COMMAND_H

#include "ClientCommand.h"

/**
* @class TeledirigidoCommand
* Comando de cambio de objetivo en el teledirigido.
*/
class TeledirigidoCommand : public ClientCommand{
private:
    int idPlayer;
    int x;
    int y;
public:
    TeledirigidoCommand(int idPlayer, int x, int y);
    void send(ProxyClient& proxy);
};

#endif