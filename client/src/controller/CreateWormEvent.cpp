#include "CreateWormEvent.h"


CreateWormEvent::CreateWormEvent(int idWorm, int idOwner, int x, int y, int dir ,
    int angle, Model&model, mainView& view):idWorm(idWorm), idOwner(idOwner), posx(x),
    posy(y), dir(dir), angle(angle), model(model), view(view){}

void CreateWormEvent::process(){
    std::string name = model.getPlayerById(idOwner);
    view.addWorm(idWorm, name, posx, posy, dir, angle);
}