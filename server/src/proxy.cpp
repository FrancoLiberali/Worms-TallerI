#include "proxy.h"
#include <arpa/inet.h>

/*typedef unsigned char uc;
#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8*/

#define MOVE_TAM 9
#define JUMP_TAM 5
#define ONEBYTE 1

Proxy::Proxy(Socket& socket_e) : socket(socket_e){
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
	char event = this->receive_char();
	switch (event){		
		case 1: //se recibe que se quiere mover un gusano
				this->receive_event_info(queue, event, MOVE_TAM);
				break;
		case 2: //se recibe que se quiere hacer saltar a un gusano 
				this->receive_event_info(queue, event, JUMP_TAM);
				break;
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

void Proxy::send_state_change(int gusano_number, char new_state){
	char event = 0;
	this->socket.send_(&event, ONEBYTE);
	char espacio = 32;
	this->socket.send_(&espacio, ONEBYTE);
	this->send_int(gusano_number);
	this->socket.send_(&espacio, ONEBYTE);
	this->socket.send_(&new_state, ONEBYTE);
}

void Proxy::send_position(int gusano_number, int x, int y, int direction, int angle){
	this->send_int(gusano_number);
	char espacio = 32;
	this->socket.send_(&espacio, ONEBYTE);
	this->send_int(x);
	this->socket.send_(&espacio, ONEBYTE);
	this->send_int(y);
	this->socket.send_(&espacio, ONEBYTE);
	this->send_int(direction);
	this->socket.send_(&espacio, ONEBYTE);
	this->send_int(angle);
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





