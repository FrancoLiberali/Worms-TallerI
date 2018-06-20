#include "PlayerIdEvent.h"
#include <iostream>
#include <string>

PlayerIdEvent::PlayerIdEvent(int id, Model& model, ProxyClient& proxy)
         :playerId(id), model(model), proxy(proxy){}

void PlayerIdEvent::process(){
    model.setIdPlayer(playerId);
    view->setIdPlayer(playerId);
}