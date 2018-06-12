#include "Model.h"
#include <iostream>

Model::Model() : idWormSelected(0){}

Model::~Model(){}

void Model::setGameControllerProxy(GameControllerProxy* gcp){
    this->gcp = gcp;
}

void Model::WormMove(const int dir){
    gcp->move(idJugador, dir);
}

void Model::WormJump(const int dir){
    gcp->jump(idJugador, dir);
}

void Model::WormWeapon(const int idWeapon){
    gcp->weapon(idJugador, idWeapon);
}

void Model::AimChangeAngle(const int delta){
    gcp->aimAngle(idJugador, delta);
}

int Model::getIdWormSelected(){
    return this->idWormSelected;
}

void Model::setIdPlayer(int idJugador){
    //std::cout<<"se agrega player id"<< std::endl;
    this->idJugador = idJugador;
}

void Model::addPlayers(int id, std::string name){
    this->players[id] = name;
}

std::string Model::getPlayerById(int id){
    return this->players[id];
}

void Model::selectWorm(int idWorm){
    idWormSelected = idWorm;
}

void Model::setNamePlayer(std::string name){
    namePlayer = name;
}

std::string Model::getNamePlayer(){
    return namePlayer;
}

bool Model::isPlayer(int id){
    return idJugador == id;
}


void Model::setComunnication(ClientCommandSender* sender, ClientEventReceiver* receiver){
    this->sender = sender;
    this->receiver = receiver;
}
void Model::closeComunnication(){
    sender->stop();
    receiver->stop();
}