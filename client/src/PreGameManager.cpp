#include "PreGameManager.h"

PreGameManager::PreGameManager(ProxyClient& proxy):proxy(proxy){
    hall = new mapWindow(proxy);
}


void PreGameManager::showHall(){
    hall->exec();
}

void PreGameManager::addMap(std::string nameMap){
    hall->addMap(nameMap);
}

