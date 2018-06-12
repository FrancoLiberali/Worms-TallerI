#include "PlayerIdEvent.h"
#include <iostream>
#include <string>

PlayerIdEvent::PlayerIdEvent(int id, Model& model, ProxyClient& proxy)
         :playerId(id), model(model), proxy(proxy){}

void PlayerIdEvent::process(){
    model.setIdPlayer(playerId);
    //std::cout<<"player Id :"<< playerId << std::endl;

    if (playerId == 1){
        printf("-------CREACION DE JUEGO------\n");
        std::string numPlayers;
        std::string idMap;
        printf("Ingrese la id del Mapa: ");
	    getline(std::cin, idMap);
        printf("Ingrese el numero de jugadores (2-10): ");
	    getline(std::cin, numPlayers);
        proxy.sendMapAndPlayers(stoi(idMap), stoi(numPlayers));
    }
    printf("Esperando por otros jugadores...........\n");
    std::string name = model.getNamePlayer();
    proxy.sendName(playerId, name);
}