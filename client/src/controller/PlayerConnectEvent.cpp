#include "PlayerConnectEvent.h"

#include <iostream>

PlayerConnectEvent::PlayerConnectEvent(int id, std::string& name, Model& model)
    :playerId(id), name(name), model(model){};

void PlayerConnectEvent::process(){
    std::cout<<"jugador conectado :"<< name << std::endl;
    model.addPlayers(playerId, name);
}