#include "proxy.h"
#include <arpa/inet.h>
#include "socket_error.h"
#include <iostream>

#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8

#define TWO_INTS 8
#define DISCONNECT_TAM 5
#define GAME_INFO_TAM 9
#define MOVE_TAM 9
#define JUMP_TAM 5
#define WEAPON_TAM 9
#define ANGLE_TAM 9
#define TIME_TAM 9
#define POWER_TAM 5
#define SHOT_TAM 5
#define ONEBYTE 1

Proxy::Proxy(Socket socket_e) : socket(std::move(socket_e)){
}
		
Proxy::~Proxy() noexcept{
}

void Proxy::close_communication(){
	this->socket.shutdown();
}

void Proxy::receive_event(ProtectedQueue& queue){
	try{
		char event = this->receive_char();
		switch (event){
			case 0: {//se recibe el nombre de un jugador
					char* buff = new char[TWO_INTS];
					this->socket.receive(buff, TWO_INTS);
					int name_len = ntohl(*(reinterpret_cast<int*>(buff + 4)));
					char* msj = new char[TWO_INTS + 1 + name_len];
					msj[0] = 0;
					msj[1] = buff[0];
					msj[2] = buff[1];
					msj[3] = buff[2];
					msj[4] = buff[3];
					msj[5] = buff[4];
					msj[6] = buff[5];
					msj[7] = buff[6];
					msj[8] = buff[7];
					this->socket.receive(msj + 9, name_len);
					queue.push(msj);
					delete[] buff;
					break;	
				}				
			case 1: //se recibe el map_id y el numero de jugadores
					this->receive_event_info(queue, event, GAME_INFO_TAM);
					break;
			case 2: //se recibe que se quiere mover un gusano
					this->receive_event_info(queue, event, MOVE_TAM);
					break;
			case 3: //se recibe que se quiere hacer saltar a un gusano 
					this->receive_event_info(queue, event, JUMP_TAM);
					break;
			case 4: //se recibe que se quiere hacer saltar hacia atras a un gusano 
					this->receive_event_info(queue, event, JUMP_TAM);
					break;
			case 5: //se recibe que un gusano saco un arma
					this->receive_event_info(queue, event, WEAPON_TAM);
					break;
			case 6: //se recibe que un gusano cambio angulo de apuntado
					this->receive_event_info(queue, event, ANGLE_TAM);
					break;
			case 7:	//se recibe que se quiere cambiar el tiempo de la cuenta regresiva
					this->receive_event_info(queue, event, TIME_TAM);
					break;
			case 8: //se recibe que se carga la barra de poder
					this->receive_event_info(queue, event, POWER_TAM);
					break;
			case 9: //se recibe que se quiere disparar
					this->receive_event_info(queue, event, SHOT_TAM);
					break;
			}
	}catch (SocketError& e){
		std::cout << "se desconecto\n";
		std::cout << this->id << "\n";
		char* msj = new char[DISCONNECT_TAM];
		//player get desconected message
		msj[0] = 1;
		msj[1] = (this->id >> MOSTSIGNIFICANT) & LAST8;
		msj[2] = (this->id >> SECONDBYTE) & LAST8;
		msj[3] = (this->id >> THIRDBYTE) & LAST8;
		msj[4] = this->id & LAST8;
		queue.push(msj);
		throw e;
	}
}

void Proxy::receive_event_info(ProtectedQueue& queue, char event, int tam){
	char* msj = new char[tam];
	msj[0] = event;
	this->socket.receive(msj+1, tam-1);
	queue.push(msj);
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

void Proxy::sendPlayerName(int player_id, std::string& name){
	char event = 1;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(name.length());
	this->socket.send(name.data(), name.length());
}

void Proxy::sendVigaCreation(int x, int y, int angle){
	char event = 2;
	this->socket.send(&event, ONEBYTE);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
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

void Proxy::sendProjectilePosition(int projectile_number, int weapon, int x, int y, int angle){
	char event = 8;
	this->socket.send(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(weapon);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::sendProjectileExplosion(int projectile_number, int x, int y){
	char event = 9;
	this->socket.send(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(x);
	this->send_int(y);
}

void Proxy::sendTakeWeapon(int weapon){
	char event = 10;
	this->socket.send(&event, ONEBYTE);
	this->send_int(weapon);
}

void Proxy::sendChangeSightAngle(int change){
	char event = 11;
	this->socket.send(&event, ONEBYTE);
	this->send_int(change);
}

void Proxy::sendLifeChange(int gusano_id, int new_life){
	char event = 12;
	this->socket.send(&event, ONEBYTE);
	this->send_int(gusano_id);
	this->send_int(new_life);
}

void Proxy::sendPlayerDisconnection(int player_id){
	char event = 13;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::sendGameWon(int player_id){
	char event = 14;
	this->socket.send(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::send_int(int to_send){
	int net_to_send = htonl(to_send);
	char* number = (char*)&net_to_send;
	this->socket.send(number, 4);
}
