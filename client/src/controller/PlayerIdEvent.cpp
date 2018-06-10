#include "PlayerIdEvent.h"
#include <iostream>

PlayerIdEvent::PlayerIdEvent(int id, Model& model, ProxyClient& proxy)
         :playerId(id), model(model), proxy(proxy){}

void PlayerIdEvent::process(){
    model.setIdPlayer(playerId);
    std::cout<<"player Id :"<< playerId << std::endl;

    if (playerId == 1){
        /*Mostrar ventan para enviar*/
         //id_mapa, num_players
        proxy.sendMapAndPlayers(1, 2);
    }
    std::string name = model.getNamePlayer();
    proxy.sendName(name);
}