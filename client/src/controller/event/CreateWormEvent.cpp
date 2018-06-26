#include "CreateWormEvent.h"
#include <iostream>

CreateWormEvent::CreateWormEvent(int idWorm, int idOwner, int x, int y, int dir ,int angle)
    :idWorm(idWorm), idOwner(idOwner), posx(x),posy(y), dir(dir), angle(angle){}

void CreateWormEvent::process(){
    std::string name = model->getPlayerById(idOwner);
    view->addWorm(idWorm, idOwner, name, posx, posy, dir, angle);
}