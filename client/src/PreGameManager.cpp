#include "PreGameManager.h"

PreGameManager::PreGameManager(ProxyClient& proxy):proxy(proxy){
    hall = new mapWindow(proxy);
    result = new resultwindow(proxy);
}

 PreGameManager::~PreGameManager(){
     delete hall;
     delete result;
 }

bool PreGameManager::showHall(){
   return (hall->exec() == QDialog::Accepted);
}

void PreGameManager::addMap(std::string nameMap){
    hall->addMap(nameMap);
}

void PreGameManager::addRoom(Room* room){
    hall->addRoom(room);
}


void PreGameManager::setResult(std::string result){
    this->result->setResult(result);
}

bool PreGameManager::showResult(){
    return (this->result->exec() == QDialog::Accepted);
}
