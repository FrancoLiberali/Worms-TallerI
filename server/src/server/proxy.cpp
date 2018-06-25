#include "server/proxy.h"
#include <arpa/inet.h>
#include "server/socket_error.h"
#include <iostream>
#include <cstring>

#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8

#define SIZE_INT 4
#define DISCONNECT_TAM 5
#define MOVE_TAM 9
#define JUMP_TAM 5
#define WEAPON_TAM 9
#define ANGLE_TAM 9
#define TIME_TAM 9
#define POWER_TAM 5
#define SHOT_TAM 5
#define EXIT_TAM 5
#define CONNECT_TAM 9
#define TELE_TAM 13
#define ONEBYTE 1

Proxy::Proxy(Socket socket_e, Queue* queue_e) : socket(std::move(socket_e)), queue(queue_e){
}

Proxy::Proxy(Proxy&& other) : socket(std::move(other.socket)), id(other.id), queue(other.queue),
		prev_queue(other.prev_queue){
}
		
Proxy::~Proxy() noexcept{
}

void Proxy::closeCommunication(){
	this->socket.shutdown();
}

void Proxy::addNewQueue(Queue* queue){
	std::lock_guard<std::mutex> lock(this->queue_mutex);
	this->prev_queue = this->queue;
	this->queue = queue;
}

void Proxy::changeToPrevQueue(){
	std::lock_guard<std::mutex> lock(this->queue_mutex);
	this->queue = this->prev_queue;
}

const std::string Proxy::receiveName(){
	char* buff = new char[SIZE_INT];
	this->socket.receive(buff, SIZE_INT);
	int name_len = ntohl(*(reinterpret_cast<int*>(buff)));
	delete[] buff;
	char* name_c = new char[name_len];
	this->socket.receive(name_c, name_len);
	std::string name(name_c, name_len);
	delete[] name_c;
	return std::move(name);
}	

void Proxy::receiveEvent(){
	try{
		char event = this->receiveChar();
		switch (event){
			case 2: //se recibe que se quiere mover un gusano
					this->receiveEventInfo(event, MOVE_TAM);
					break;
			case 3: //se recibe que se quiere hacer saltar a un gusano 
					this->receiveEventInfo(event, JUMP_TAM);
					break;
			case 4: //se recibe que se quiere hacer saltar hacia atras a un gusano 
					this->receiveEventInfo(event, JUMP_TAM);
					break;
			case 5: //se recibe que un gusano saco un arma
					this->receiveEventInfo(event, WEAPON_TAM);
					break;
			case 6: //se recibe que un gusano cambio angulo de apuntado
					this->receiveEventInfo(event, ANGLE_TAM);
					break;
			case 7:	//se recibe que se quiere cambiar el tiempo de la cuenta regresiva
					this->receiveEventInfo(event, TIME_TAM);
					break;
			case 8: //se recibe que se carga la barra de poder
					this->receiveEventInfo(event, POWER_TAM);
					break;
			case 9: //se recibe que se quiere disparar
					this->receiveEventInfo(event, SHOT_TAM);
					break;
			case 11://se recibe que se quiere salir de la room actual
					this->receiveEventInfo(event, EXIT_TAM);
					break;
			case 12://se recibe que se quiere entrar a una room
					this->receiveEventInfo(event, CONNECT_TAM);
					break;	
			case 13:{//se recibe que se quiere crear una room
					char* buff = new char[3 * SIZE_INT];
					this->socket.receive(buff, 3 * SIZE_INT);
					int map_len = ntohl(*(reinterpret_cast<int*>(buff + 2 * SIZE_INT)));
					char* map_name = new char[map_len];
					this->socket.receive(map_name, map_len);
					char* buff2 = new char[1 * SIZE_INT];
					this->socket.receive(buff2, 1 * SIZE_INT);
					int name_len = ntohl(*(reinterpret_cast<int*>(buff2)));
					char* name = new char[name_len];
					this->socket.receive(name, name_len);
					char* msj = new char[4 * SIZE_INT + 1 + map_len + name_len];
					msj[0] = event;
					memcpy(msj+1, buff, 3 * SIZE_INT);
					delete[] buff;
					memcpy(msj+13, map_name, map_len);
					delete[] map_name;
					memcpy(msj+13+map_len, buff2, SIZE_INT);
					delete[] buff2;
					memcpy(msj+17+map_len, name, name_len);
					delete[] name;
					this->queue->push(msj);
					break;
				}
			case 14://se recibe que se quiere modificar el apuntado del teledirigido
					std::cout << "llego 14 \n";
					this->receiveEventInfo(event, TELE_TAM);
					break;	
			}
	}catch (SocketError& e){
		std::cout << "se desconecto\n";
		std::cout << this->id << "\n";
		this->pushDisconnectionMessage();
		throw e;
	}
}

void Proxy::pushDisconnectionMessage(){
	char* msj = new char[DISCONNECT_TAM];
	//player get disconected message
	msj[0] = 10;
	msj[1] = (this->id >> MOSTSIGNIFICANT) & LAST8;
	msj[2] = (this->id >> SECONDBYTE) & LAST8;
	msj[3] = (this->id >> THIRDBYTE) & LAST8;
	msj[4] = this->id & LAST8;
	std::lock_guard<std::mutex> lock(this->queue_mutex);
	this->queue->push(msj);
}

void Proxy::disconnect(){
	this->changeToPrevQueue();
	this->pushDisconnectionMessage();
}

void Proxy::receiveEventInfo(char event, int tam){
	char* msj = new char[tam];
	msj[0] = event;
	this->socket.receive(msj+1, tam-1);
	std::lock_guard<std::mutex> lock(this->queue_mutex);
	this->queue->push(msj);
}

const unsigned char Proxy::receiveChar(){
	char received;
	this->socket.receive(&received, ONEBYTE);
	return received;
}

void Proxy::sendPlayerId(const int id){
	char event = 0;
	this->socket.send(&event, ONEBYTE);
	this->id = id;
	this->sendInt(id);
}

void Proxy::sendMapBackground(const std::string& background){
	char event = 1;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(background.length());
	this->socket.send(background.data(), background.length());
}

void Proxy::sendVigaCreation(int x, int y, int angle){
	char event = 2;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(x);
	this->sendInt(y);
	this->sendInt(angle);
}

void Proxy::sendMapDimentions(int widht, int height){
	char event = 3;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(widht);
	this->sendInt(height);
}

void Proxy::sendGusanoCreation(int gusano_id, int player_id, int x, int y, int direction, int angle){
	char event = 4;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(gusano_id);
	this->sendInt(player_id);
	this->sendInt(x);
	this->sendInt(y);
	this->sendInt(direction);
	this->sendInt(angle);
}

void Proxy::sendTurnBegining(int player_id, int gusano_id){
	char event = 5;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(player_id);
	this->sendInt(gusano_id);
}

void Proxy::sendGusanoPosition(int gusano_id, int x, int y, int direction, int angle){
	char event = 6;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(gusano_id);
	this->sendInt(x);
	this->sendInt(y);
	this->sendInt(direction);
	this->sendInt(angle);
}

void Proxy::sendStateChange(int gusano_id, int new_state){
	char event = 7;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(gusano_id);
	this->sendInt(new_state);
}

void Proxy::sendProjectileCreation(int projectile_number, int weapon, int direction, int x, int y, int angle){
	char event = 8;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(projectile_number);
	this->sendInt(weapon);
	this->sendInt(direction);
	this->sendInt(x);
	this->sendInt(y);
	this->sendInt(angle);
}

void Proxy::sendProjectilePosition(int projectile_number, int x, int y, int angle){
	char event = 9;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(projectile_number);
	this->sendInt(x);
	this->sendInt(y);
	this->sendInt(angle);
}

void Proxy::sendProjectileExplosion(int projectile_number){
	char event = 10;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(projectile_number);
}

void Proxy::sendTakeWeapon(int weapon){
	char event = 11;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(weapon);
}

void Proxy::sendChangeSightAngle(int change){
	char event = 12;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(change);
}

void Proxy::sendLifeChange(int gusano_id, int new_life){
	char event = 13;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(gusano_id);
	this->sendInt(new_life);
}

void Proxy::sendPlayerDisconnection(int player_id){
	char event = 14;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(player_id);
}

void Proxy::sendPlayerLoose(int player_id){
	char event = 15;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(player_id);
	if (player_id == this->id){
		this->changeToPrevQueue();
	}
}

void Proxy::sendGameWon(int player_id){
	char event = 16;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(player_id);
}

void Proxy::sendRoomCreation(const int room_id, const std::string& name, const int cant_players, 
							 const int max_players, const std::string& map_name){
	char event = 17;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(room_id);
	this->sendInt(name.length());
	this->socket.send(name.data(), name.length());
	this->sendInt(cant_players);
	this->sendInt(max_players);
	this->sendInt(map_name.length());
	this->socket.send(map_name.data(), map_name.length());
}

void Proxy::sendRoomPlayersChange(int room_id, int cant_players){
	char event = 18;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(room_id);
	this->sendInt(cant_players);
}

void Proxy::sendRoomDeletion(int room_id){
	char event = 19;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(room_id);
}

void Proxy::sendPlayerConnection(int id, const std::string& name){
	char event = 20;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(id);
	this->sendInt(name.length());
	this->socket.send(name.data(), name.length());
}

void Proxy::sendAvailableMaps(const std::vector<std::string>& maps){
	char event = 21;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(maps.size());
	std::vector<std::string>::const_iterator it = maps.begin();
	for (; it != maps.end(); ++it){
		this->sendInt(it->length());
		this->socket.send(it->data(), it->length());
	}
}

void Proxy::sendFinishedAmunnition(int weapon_id){
	char event = 22;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(weapon_id);
}

void Proxy::sendRemoteWork(int weapon_id){
	char event = 23;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(weapon_id);
}

void Proxy::sendSecond(){
	char event = 24;
	this->socket.send(&event, ONEBYTE);
}

void Proxy::sendWindChange(int wind){
	char event = 25;
	this->socket.send(&event, ONEBYTE);
	this->sendInt(wind);
}

void Proxy::sendInt(int to_send){
	int net_to_send = htonl(to_send);
	char* number = (char*)&net_to_send;
	this->socket.send(number, 4);
}
