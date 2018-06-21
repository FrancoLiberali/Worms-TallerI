#include "proxy.h"
#include <arpa/inet.h>
#include "socket_error.h"
#include <iostream>
#include <cstring>

#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8

#define SIZE_INT 4
#define DISCONNECT_TAM 5
#define GAME_INFO_TAM 9
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
		
Proxy::~Proxy() noexcept{
}

void Proxy::close_communication(){
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

std::string Proxy::receiveName(){
	char* buff = new char[4];
	this->socket.receive(buff, 4);
	int name_len = ntohl(*(reinterpret_cast<int*>(buff + 0)));
	delete[] buff;
	char* name_c = new char[name_len];
	this->socket.receive(name_c, name_len);
	std::string name(name_c, name_len);
	delete[] name_c;
	return std::move(name);
}	

void Proxy::receive_event(){
	try{
		char event = this->receive_char();
		switch (event){
			case 1: //se recibe el map_id y el numero de jugadores
					this->receive_event_info(event, GAME_INFO_TAM);
					break;
			case 2: //se recibe que se quiere mover un gusano
					this->receive_event_info(event, MOVE_TAM);
					break;
			case 3: //se recibe que se quiere hacer saltar a un gusano 
					this->receive_event_info(event, JUMP_TAM);
					break;
			case 4: //se recibe que se quiere hacer saltar hacia atras a un gusano 
					this->receive_event_info(event, JUMP_TAM);
					break;
			case 5: //se recibe que un gusano saco un arma
					this->receive_event_info(event, WEAPON_TAM);
					break;
			case 6: //se recibe que un gusano cambio angulo de apuntado
					this->receive_event_info(event, ANGLE_TAM);
					break;
			case 7:	//se recibe que se quiere cambiar el tiempo de la cuenta regresiva
					this->receive_event_info(event, TIME_TAM);
					break;
			case 8: //se recibe que se carga la barra de poder
					this->receive_event_info(event, POWER_TAM);
					break;
			case 9: //se recibe que se quiere disparar
					this->receive_event_info(event, SHOT_TAM);
					break;
			case 11://se recibe que se quiere salir de la room actual
					this->receive_event_info(event, EXIT_TAM);
					break;
			case 12://se recibe que se quiere entrar a una room
					this->receive_event_info(event, CONNECT_TAM);
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
					this->receive_event_info(event, TELE_TAM);
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

void Proxy::receive_event_info(char event, int tam){
	char* msj = new char[tam];
	msj[0] = event;
	this->socket.receive(msj+1, tam-1);
	std::lock_guard<std::mutex> lock(this->queue_mutex);
	this->queue->push(msj);
}

const unsigned char Proxy::receive_char(){
	char received;
	this->socket.receive(&received, ONEBYTE);
	return received;
}

void Proxy::sendPlayerId(int id){
	char event = 0;
	this->socket.send(&event, ONEBYTE);
	this->id = id;
	this->send_int(id);
}

void Proxy::sendMapBackground(std::string& background){
	char event = 1;
	this->socket.send(&event, ONEBYTE);
	this->send_int(background.length());
	this->socket.send(background.data(), background.length());
}

void Proxy::sendVigaCreation(int x, int y, int angle){
	char event = 2;
	this->socket.send(&event, ONEBYTE);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::sendMapDimentions(int widht, int height){
	char event = 3;
	this->socket.send(&event, ONEBYTE);
	this->send_int(widht);
	this->send_int(height);
}

void Proxy::sendGusanoCreation(int gusano_id, int player_id, int x, int y, int direction, int angle){
	char event = 4;
	this->socket.send(&event, ONEBYTE);
	this->send_int(gusano_id);
	this->send_int(player_id);
	this->send_int(x);
	this->send_int(y);
	this->send_int(direction);
	this->send_int(angle);
}

void Proxy::sendTurnBegining(int player_id, int gusano_id){
	char event = 5;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(gusano_id);
}

void Proxy::sendGusanoPosition(int gusano_id, int x, int y, int direction, int angle){
	char event = 6;
	this->socket.send(&event, ONEBYTE);
	this->send_int(gusano_id);
	this->send_int(x);
	this->send_int(y);
	this->send_int(direction);
	this->send_int(angle);
}

void Proxy::sendStateChange(int gusano_id, int new_state){
	char event = 7;
	this->socket.send(&event, ONEBYTE);
	this->send_int(gusano_id);
	this->send_int(new_state);
}

void Proxy::sendProjectileCreation(int projectile_number, int weapon, int direction, int x, int y, int angle){
	char event = 8;
	this->socket.send(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(weapon);
	this->send_int(direction);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::sendProjectilePosition(int projectile_number, int x, int y, int angle){
	char event = 9;
	this->socket.send(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::sendProjectileExplosion(int projectile_number){
	char event = 10;
	this->socket.send(&event, ONEBYTE);
	this->send_int(projectile_number);
}

void Proxy::sendTakeWeapon(int weapon){
	char event = 11;
	this->socket.send(&event, ONEBYTE);
	this->send_int(weapon);
}

void Proxy::sendChangeSightAngle(int change){
	char event = 12;
	this->socket.send(&event, ONEBYTE);
	this->send_int(change);
}

void Proxy::sendLifeChange(int gusano_id, int new_life){
	char event = 13;
	this->socket.send(&event, ONEBYTE);
	this->send_int(gusano_id);
	this->send_int(new_life);
}

void Proxy::sendPlayerDisconnection(int player_id){
	char event = 14;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::sendPlayerLoose(int player_id){
	char event = 15;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
	if (player_id == this->id){
		this->changeToPrevQueue();
	}
}

void Proxy::sendGameWon(int player_id){
	char event = 16;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::sendRoomCreation(int room_id, const std::string& name, int cant_players, int max_players, const std::string& map_name){
	char event = 17;
	this->socket.send(&event, ONEBYTE);
	this->send_int(room_id);
	this->send_int(name.length());
	this->socket.send(name.data(), name.length());
	this->send_int(cant_players);
	this->send_int(max_players);
	this->send_int(map_name.length());
	this->socket.send(map_name.data(), map_name.length());
}

void Proxy::sendRoomPlayersChange(int room_id, int cant_players){
	char event = 18;
	this->socket.send(&event, ONEBYTE);
	this->send_int(room_id);
	this->send_int(cant_players);
}

void Proxy::sendRoomDeletion(int room_id){
	char event = 19;
	this->socket.send(&event, ONEBYTE);
	this->send_int(room_id);
}

void Proxy::sendPlayerConnection(int id, const std::string& name){
	char event = 20;
	this->socket.send(&event, ONEBYTE);
	this->send_int(id);
	this->send_int(name.length());
	this->socket.send(name.data(), name.length());
}

void Proxy::sendAvailableMaps(std::vector<std::string>& maps){
	char event = 21;
	this->socket.send(&event, ONEBYTE);
	this->send_int(maps.size());
	std::vector<std::string>::iterator it = maps.begin();
	for (; it != maps.end(); ++it){
		//this->socket.send(&event, ONEBYTE);
		this->send_int(it->length());
		this->socket.send(it->data(), it->length());
	}
}

void Proxy::sendFinishedAmunnition(int weapon_id){
	char event = 22;
	this->socket.send(&event, ONEBYTE);
	this->send_int(weapon_id);
}

void Proxy::send_int(int to_send){
	int net_to_send = htonl(to_send);
	char* number = (char*)&net_to_send;
	this->socket.send(number, 4);
}
