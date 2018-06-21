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

void Model::chargePower(){
    gcp->chargePower(idJugador);
}

void Model::WormShoot(){
    gcp->shoot(idJugador);
}


void Model::countDown(int time){
    gcp->countDown(idJugador,time);
}

int Model::getIdWormSelected(){
    return this->idWormSelected;
}

void Model::setIdPlayer(int idJugador){
    this->idJugador = idJugador;
    this->players[idJugador] = this->namePlayer;
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

int Model::getIdPlayer(){
    return idJugador;
}

void Model::setComunnication(ClientCommandSender* sender, ClientEventReceiver* receiver){
    this->sender = sender;
    this->receiver = receiver;
}
void Model::closeComunnication(){
    sender->stop();
    receiver->stop();
}
