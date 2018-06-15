#include "mok_proxy.h"
#include <arpa/inet.h>
#include <iostream>
#include <string>

#define MOVE_TAM 9
#define JUMP_TAM 5
#define FIRE_SIGHT_POWER_TAM 17

MokProxy::MokProxy(Socket& socket_e): socket(socket_e){
}

MokProxy::~MokProxy(){
}

void MokProxy::close_communication(){
	this->socket.shutdown_();
}

void MokProxy::receive_event(){
	char entry = 0;
	this->socket.receive_(&entry, 1);
	switch (entry){
		case 0: {//se recibe id de jugador
				this->id = this->receive_int();
				std::cout << "0 " << this->id << "\n";
				if (this->id == 1){
					this->sendMapAndPlayers(0,2);
				}
				break;
			}
		case 1: {//se recibe nombre de jugador
				int player_id = this->receive_int();
				int name_len = this->receive_int();
				char* name_c = new char[name_len];
				this->socket.receive_(name_c, name_len);
				std::string name(name_c, name_len);
				std::cout << "1 " << player_id << " " << name << "\n";
				delete[] name_c;
				break;
			}
		case 2:{ //se recibe la posicion de una viga en el mapa
				int x = this->receive_int();
				int y = this->receive_int();
				int angle = this->receive_int();
				std::cout << "2 " << x << " " << y << " " << angle << "\n";
				break;
			}
		case 3: {//se recibe posicion del agua en el mapa
				//a definir
				break;
			}
		case 4: {//se recibe la creacion de un gusano en el mapa
				int id = this->receive_int();
				int duenio = this->receive_int();
				int x = this->receive_int();
				int y = this->receive_int();
				int direccion = this->receive_int();
				int angle = this->receive_int();
				std::cout << "4 " << id << " " << duenio << " " << x << " " << y << " " << direccion << " " << angle << "\n";
				break;
			}
		case 5: {//se recibe inicio de turno
				int jugador_actual = this->receive_int();
				int id = this->receive_int();
				std::cout << "5 " << jugador_actual << " " << id << "\n";
				break;
			}
		case 6: {//se recibe la posicion de un gusano en el mapa
				int id = this->receive_int();
				int x = this->receive_int();
				int y = this->receive_int();
				int direccion = this->receive_int();
				int angle = this->receive_int();
				std::cout << "6 " << id << " " << x << " " << y << " " << direccion << " " << angle << "\n";
				break;
			}
		case 7: {//cambio de estado de un gusano
				int id = this->receive_int();
				int new_state = this->receive_int();
				std::cout << "7 " << id << " " << new_state << "\n";
				break;
			}
		case 8:{//creacion proyectil en el mapa
				int id = this->receive_int();
				int arma = this->receive_int();
				int direccion = this->receive_int();
				int x = this->receive_int();
				int y= this->receive_int();
				int angle = this->receive_int();
				std::cout << "8 " << id << " " << arma << " " << direccion << " " << x << " " << y << " " << angle << "\n";
				break;
			}
		case 9:{//posicion de un proyectil en el mapa
				int id = this->receive_int();
				int x = this->receive_int();
				int y= this->receive_int();
				int angle = this->receive_int();
				std::cout << "9 " << id << " " << x << " " << y << " " << angle << "\n";
				break;
			}
		case 10:{//explocion de un proyectil
				int id = this->receive_int();
				std::cout << "10 " << id << "\n";
				break;
			}
		case 11:{//gusano actual saco arma
				int arma = this->receive_int();
				std::cout << "11 " << arma << "\n";
				break;
			}
		case 12:{//gusano cambio angulo de aputado
				int cambio = this->receive_int();
				std::cout << "12 " << cambio << "\n";
				break;
			}
		case 13: {//gusano cambio de vida
				int id = this->receive_int();
				int new_life = this->receive_int();
				std::cout << "13 " << id << " " << new_life << "\n";
				break;
			}
		case 14: {//jugador desconectado
			int id = this->receive_int();
			std::cout << "14 " << id << "\n";
			break;
		}
		case 15: {//jugador gano la partida
			int id = this->receive_int();
			std::cout << "15 " << id << "\n";
			break;
		}
	}
}

int MokProxy::receive_int(){
	char* buff = new char[4];
	this->socket.receive_(buff, 4);
	int received = ntohl(*(reinterpret_cast<int*>(buff + 0)));
	delete[] buff;
	return (received);
}

void MokProxy::sendMapAndPlayers(int map, int players){
	std::cout << "map\n";
	char ev = 1;
	this->socket.send_(&ev, 1);
	this->send_int(map);
	this->send_int(players);
}

void MokProxy::send(char event){
	switch (event){
		case 'n': {//mandar nombre
				std::cout << "name\n";
				char ev = 0;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				char name[5] = "pepe";
				this->send_int(4);
				this->socket.send_(name, 4);
				break;
			}
		case 'a': {//mover un gusano a la izquierda
				std::cout << "izquierda\n";
				char ev = 2;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				//izquierda = -1
				this->send_int(-1);
				break;
			}
		case 'd':{ //mover un gusano a la derecha
				std::cout << "derecha\n";
				char ev = 2;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				//derecha = 1
				this->send_int(1);
				break;
			}
		case 'j': {//hacer saltar al gusano
				std::cout << "salto\n";
				char ev = 3;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				break;
			}
		case 'h': {//hacer saltar atras al gusano
				std::cout << "salto\n";
				char ev = 4;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				break;
			}
		case 'b': {//sacar bazooka
				std::cout << "bazooka\n";
				char ev = 5;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				this->send_int(1);
				break;
			}
		case 'm': {//sacar mortero
				std::cout << "mortero\n";
				char ev = 5;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				this->send_int(2);
				break;
			}
		case 'w': {//apuntar mas arriba
				std::cout << "mas arriba\n";
				char ev = 6;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				this->send_int(1);
				break;
			}
		case 's': {//apuntar mas abajo
				std::cout << "mas abajo\n";
				char ev = 6;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				this->send_int(-1);
				break;
			}
		case '1': {//cuenta regresiva a 1
				std::cout << "a 1\n";
				char ev = 7;
				this->socket.send_(&ev, 1);
				this->send_int(this->id);
				this->send_int(1);
				break;
			}
		case '2': {//cuenta regresiva a 2
			std::cout << "a 2\n";
			char ev = 7;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			this->send_int(2);
			break;
		}
		case '3': {//cuenta regresiva a 3
			std::cout << "a 3\n";
			char ev = 7;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			this->send_int(3);
			break;
		}
		case '4': {//cuenta regresiva a 4
			std::cout << "a 4\n";
			char ev = 7;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			this->send_int(4);
			break;
		}
		case '5': {//cuenta regresiva a 5
			std::cout << "a 5\n";
			char ev = 7;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			this->send_int(5);
			break;
		}
		case 'c': {//cargar arma
			std::cout << "cargar\n";
			char ev = 8;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			break;
		}
		case 'v':{//dejar de cargar(mensaje que se deberia mandar cuando se suelta la c pero asi no lo puedo hacer
			std::cout << "dejar de cargar\n";
			char ev = 9;
			this->socket.send_(&ev, 1);
			this->send_int(this->id);
			break;
		}
	}
}
	
void MokProxy::send_int(int to_send){
	int net_to_send = htonl(to_send);
	char* number = (char*)&net_to_send;
	this->socket.send_(number, 4);
}
