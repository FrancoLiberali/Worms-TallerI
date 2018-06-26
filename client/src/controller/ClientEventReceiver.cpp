#include "ClientEventReceiver.h"
#include "../Room.h"
#include "EventFactory.h"
#include "EventType.h"
#include <string>
#include <iostream>
#include <vector>

#define MIN_PRE_EVENT 17
#define MAX_PRE_EVENT 21

ClientEventReceiver::ClientEventReceiver(ProxyClient& proxy, Queue<Event*>& q,
	Model& model, mainView& view, PreGameManager& preGame)
	: proxy(proxy), q(q), model(model), closed(false), view(view), preGame(preGame){	
}


ClientEventReceiver::~ClientEventReceiver() {
 while (!q.empty()) {
    	delete q.pop();
  	}
}

void ClientEventReceiver::run(){
	try{
		while (!closed){
			char t = proxy.receiveChar();
			if (isPreGameEvent((int)t)){
				process(t);
				continue;
			}
			EventType type = static_cast<EventType>(t);
			Event* event = EventFactory::createEvent(type, proxy);
			q.push(event);
		}
	} catch (SocketError& e){
		this->stop();
	}

}

bool ClientEventReceiver::isPreGameEvent(int t){
	return  (t >= MIN_PRE_EVENT && t <= MAX_PRE_EVENT )|| t == ID_PLAYER 
			|| t == A_PLAYER_LOSE || t == A_PLAYER_WIN;
}

//Manejo de eventos que son previos o después de juego principal
//nos son encolados en la cola de eventos
void ClientEventReceiver::process(int t){
	switch (t){
		case ID_PLAYER:{
			int id = proxy.receiveInt();
			model.setIdPlayer(id);
			break;
		}
		case NEW_ROOM:{
			int idRoom = proxy.receiveInt();
			std::string nameRoom = proxy.receiveName();
			int currPlayers = proxy.receiveInt();
			int numPlayers = proxy.receiveInt();
			std::string mapName = proxy.receiveName();
			Room* room = new Room(idRoom, nameRoom, numPlayers, mapName);
			room->updateCurrPlayers(currPlayers);
			preGame.addRoom(room);
			break;
		}
		case CHANGE_N_PLAYERS_IN_ROOM:
			std::cout << 18 <<std::endl;
			break;
		case DEL_ROOM:
			std::cout << 19 <<std::endl;
			break;
		case NEW_PLAYER_IN_ROOM:{
			int idPlayer = proxy.receiveInt();
			std::string namePlayer = proxy.receiveName();
			model.addPlayers(idPlayer, namePlayer);
			break;
		}
		case ALLOW_MAPS:{
			int size = proxy.receiveInt();
			for (int i = 0; i < size; i++){
				std::string name_map = proxy.receiveName();
				preGame.addMap(name_map);
			}
			break;
		}
		case A_PLAYER_LOSE:{
			int idPlayer = proxy.receiveInt();
			std::string name = model.getPlayerById(idPlayer);
			if (model.isPlayer(idPlayer)){
				preGame.setResult("Loser");
				view.close();
			}else{
				view.showLosser(idPlayer, name);
			}
			break;
		}
		case A_PLAYER_WIN:{
			int idPlayer = proxy.receiveInt();
			if (model.isPlayer(idPlayer))
				preGame.setResult("Winner");
			else
				preGame.setResult("Loser");
			view.close();
			break;
		}
	}
}

void ClientEventReceiver::stop(){
	if (closed)
		return;
	closed = true;
	proxy.close();
}

bool ClientEventReceiver::isClosed() const{
	return closed;
}

void ClientEventReceiver::keepPlaying(){
	view.openWindow();
}

void ClientEventReceiver::clean(){
	
}