#include "Model.h"

Model::Model(GameControllerProxy& gcp): gcp(gcp), idWormSelected(2){}

Model::~Model(){}

void Model::WormMove(const int dir){
    gcp.move(idJugador, dir);
}

void Model::WormJump(const int dir){
    gcp.jump(idJugador, dir);
}

void Model::WormWeapon(const int idWeapon){
    gcp.weapon(idJugador, idWeapon);
}

int Model::getIdWormSelected(){
    return this->idWormSelected;
}