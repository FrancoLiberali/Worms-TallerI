#include "proxy.h"
#include <arpa/inet.h>
#include "socket_error.h"
#include <iostream>


#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8

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
	this->socket.shutdown_();
}

/*//estos no estarian en el proxy del client
//pero tener en cuenta a la hora de recibir
// (boseto en receive event)
void Proxy::send_viga(Socket& socket, const Viga& viga){
	this->send_char(socket, 0); //0 = recibir una posicion
	this->send_char(socket, 0); //0 = la posicion corresponde a una viga
	// a continuacion se recibe la posicion segun formato en send_position
	b2Vec2 position = viga.GetPosition();
	this->send_position(socket, position);
	float angle = viga.GetAngle();
	this->send_float(socket, angle);
}
		
void Proxy::send_gusano(Socket& socket, const Gusano& gusano, unsigned int number){
	this->send_char(socket, 0); //0 = recibir una posicion
	this->send_char(socket, 1); //1 = la posicion corresponde a un gusano
	// se envia el numero de gusano(se deberia meter en un vector en este orden a que el numero va a ser quien
	// represente a ese gusano de aqui en adelante
	this->send_unsigned_int(socket, number);
	// a continuacion se recibe la posicion segun formato en send_position
	b2Vec2 position = gusano.GetPosition();
	this->send_position(socket, position);
	//y el angulo como un float
	float angle = gusano.GetAngle();
	this->send_float(socket, angle);
}

void Proxy::send_movement(Socket& socket, unsigned int gusano_number, int direction){
	this->send_char(socket, 1); //1 = movimiento
	this->send_unsigned_int(gusano_number);
	this->send_int(direction);
}
		
void Proxy::send_position(Socket& socket, const b2Vec2& pos){
	this->send_float(socket, pos.x);
	this->send_float(socket, pos.y);
}

void Proxy::send_unsigned_int(Socket& socket, unsigned int num){
	char c1 = (num >> MOSTSIGNIFICANT) & LAST8;
	char c2 = (num >> SECONDBYTE) & LAST8;
	char c3 = (num >> THIRDBYTE) & LAST8;
	char c4 = num & LAST8;
	this->send_char(socket, c1);
	this->send_char(socket, c2);
	this->send_char(socket, c3);
	this->send_char(socket, c4);
}

void Proxy::send_int(Socket& socket, int num){
	char c1 = (num >> MOSTSIGNIFICANT) & LAST8;
	char c2 = (num >> SECONDBYTE) & LAST8;
	char c3 = (num >> THIRDBYTE) & LAST8;
	char c4 = num & LAST8;
	this->send_char(socket, c1);
	this->send_char(socket, c2);
	this->send_char(socket, c3);
	this->send_char(socket, c4);
}

void Proxy::send_float(Socket& socket, float num){
	char c1 = (num >> MOSTSIGNIFICANT) & LAST8;
	char c2 = (num >> SECONDBYTE) & LAST8;
	char c3 = (num >> THIRDBYTE) & LAST8;
	char c4 = num & LAST8;
	this->send_char(socket, c1);
	this->send_char(socket, c2);
	this->send_char(socket, c3);
	this->send_char(socket, c4);
}

void Proxy::send_char(Socket& socket, const char to_send){
	 socket.send_(&to_send, ONEBYTE);
}*/

void Proxy::receive_event(ProtectedQueue& queue){
	try{
		char event = this->receive_char();
		switch (event){
			case 0: //se recibe el map_id y el numero de jugadores
					this->receive_event_info(queue, event, GAME_INFO_TAM);
					break;
			case 1: //se recibe que se quiere mover un gusano
					this->receive_event_info(queue, event, MOVE_TAM);
					break;
			case 2: //se recibe que se quiere hacer saltar a un gusano 
					this->receive_event_info(queue, event, JUMP_TAM);
					break;
			case 3: //se recibe que se quiere hacer saltar hacia atras a un gusano 
					this->receive_event_info(queue, event, JUMP_TAM);
					break;
			case 4: //se recibe que un gusano saco un arma
					this->receive_event_info(queue, event, WEAPON_TAM);
					break;
			case 5: //se recibe que un gusano cambio angulo de apuntado
					this->receive_event_info(queue, event, ANGLE_TAM);
					break;
			case 6:	//se recibe que se quiere cambiar el tiempo de la cuenta regresiva
					this->receive_event_info(queue, event, TIME_TAM);
					break;
			case 7: //se recibe que se carga la barra de poder
					this->receive_event_info(queue, event, POWER_TAM);
					break;
			case 8: //se recibe que se quiere disparar
					this->receive_event_info(queue, event, SHOT_TAM);
					break;
			}
	}catch (SocketError& e){
		std::cout << "se desconecto\n";
		std::cout << this->id << "\n";
		char* msj = new char[DISCONNECT_TAM];
		//player get desconected message
		msj[0] = 0;
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
	this->socket.receive_(msj+1, tam-1);
	queue.push(msj);
}

const unsigned char Proxy::receive_char(){
	char received;
	this->socket.receive_(&received, ONEBYTE);
	return received;
}

void Proxy::sendPlayerId(int id){
	char event = 0;
	this->socket.send_(&event, ONEBYTE);
	this->id = id;
	this->send_int(id);
}

void Proxy::send_viga_position(int x, int y, int angle){
	char event = 1;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::send_gusano_position(int player_id, int gusano_id, int x, int y, int direction, int angle){
	char event = 3;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(gusano_id);
	this->send_int(x);
	this->send_int(y);
	this->send_int(direction);
	this->send_int(angle);
}

void Proxy::sendTurnBegining(int player_id, int gusano_id){
	char event = 4;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(gusano_id);
}

void Proxy::send_state_change(int player_id, int gusano_id, int new_state){
	char event = 5;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(gusano_id);
	this->send_int(new_state);
}

void Proxy::send_projectile_creation(int projectile_number, int weapon, int x, int y, int angle){
	char event = 6;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(weapon);
	this->send_int(x);
	this->send_int(y);
	this->send_int(angle);
}

void Proxy::sendProjectileExplosion(int projectile_number, int x, int y){
	char event = 7;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(projectile_number);
	this->send_int(x);
	this->send_int(y);
}

void Proxy::sendTakeWeapon(int weapon){
	char event = 8;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(weapon);
}

void Proxy::sendChangeSightAngle(int change){
	char event = 9;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(change);
}

void Proxy::sendLifeChange(int player_id, int gusano_id, int new_life){
	char event = 10;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
	this->send_int(gusano_id);
	this->send_int(new_life);
}

void Proxy::sendPlayerDisconnection(int player_id){
	char event = 11;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::sendGameWon(int player_id){
	char event = 12;
	this->socket.send_(&event, ONEBYTE);
	this->send_int(player_id);
}

void Proxy::send_int(int to_send){
	int net_to_send = htonl(to_send);
	char* number = (char*)&net_to_send;
	this->socket.send_(number, 4);
}


	
	

/*const float Proxy::receive_float(Socket& socket){
	char c1 = this->receive_char(socket);
	char c2 = this->receive_char(socket);
	char c3 = this->receive_char(socket);
	char c4 = this->receive_char(socket);
	float received = (((uc)c1 << MOSTSIGNIFICANT) 
					 | ((uc)c2 << SECONDBYTE) 
					 | ((uc)c3 << THIRDBYTE) 
					 | ((uc)c4));
	return received;
}

const unsigned int Proxy::receive_unsigned_int(Socket& socket){
	char c1 = this->receive_char(socket);
	char c2 = this->receive_char(socket);
	char c3 = this->receive_char(socket);
	char c4 = this->receive_char(socket);
	unsigned int received = (((uc)c1 << MOSTSIGNIFICANT) 
							| ((uc)c2 << SECONDBYTE) 
							| ((uc)c3 << THIRDBYTE) 
							| ((uc)c4));
	return received;
}

const int Proxy::receive_int(Socket& socket){
	char c1 = this->receive_char(socket);
	char c2 = this->receive_char(socket);
	char c3 = this->receive_char(socket);
	char c4 = this->receive_char(socket);
	int received = (((uc)c1 << MOSTSIGNIFICANT) 
					| ((uc)c2 << SECONDBYTE) 
					| ((uc)c3 << THIRDBYTE) 
					| ((uc)c4));
	return received;
}*/





