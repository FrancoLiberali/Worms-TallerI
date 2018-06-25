#ifndef _CHARGE_POWER_COMMAND_H
#define _CHARGE_POWER_COMMAND_H

#include "ClientCommand.h"

/**
* @class ChargePowerCommand
* Comando de carga de arma.
*/

class ChargePowerCommand : public ClientCommand{
private:
    int idJugador;
public:
    ChargePowerCommand(int idJugador);
    void send(ProxyClient& proxy);
};

#endif