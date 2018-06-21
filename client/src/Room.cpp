#include "Room.h"

Room::Room(int idRoom, std::string& name, int numPlayers, std::string& map)
    :id(idRoom), name(name), numPlayers(numPlayers), mapName(map){}

int Room::getId(){
    return this->id;
}

int Room::getNumPlayers(){
    return numPlayers;
}

std::string Room::getMap(){
    return mapName;
}

std::string Room::getName(){
    return name;
}

void Room::updateCurrPlayers(int currPlayers){
    this->currPlayers = currPlayers;
}

int Room::getCurrPlayers(){
    return this->currPlayers;
}

bool Room::isName(std::string& name){
    return this->name == name;
}


