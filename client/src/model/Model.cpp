#include "Model.h"

Model::Model(GameControllerProxy& gcp): gcp(gcp), idWormSelected(1){}

Model::~Model(){}

void Model::KeyWormMove(int dir){
    gcp.move(idWormSelected, dir);
}

void Model::KeyWormJump(){

}

void Model::leftClick(){

}