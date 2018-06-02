#include "proxy.h"

typedef unsigned char uc;
#define LAST8 0xFF
#define MOSTSIGNIFICANT 24
#define SECONDBYTE 16
#define THIRDBYTE 8

Proxy::Proxy(){
}
		
Proxy::~Proxy() noexcept{
}

//estos no estarian en el proxy del client
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
}

//la firma de la funcion probablemente sea distinta en el client porque van a hacer cosas distintas
void Proxy::receive_event(Socket& socket, Turn& turn){
	char event = this->receive_char(socket);
	switch (event){
		//en cliente va a estar:
		//case 0: //llamar a codigo client para cuando se recibe viga o gusano
					//aca no porque no existe este caso
					//char what = this->receive_char(socket);
					//float x = this->receive_float(socket);
					//float y = this->receive_float(socket);
					//float angle = this->receive_float(socket);
					//if (what == 0){
						//model.mostrar_viga(x, y, angle) o algo asi vos fijate
					//else if (what == 1){
						//model.mostrar_gusano(x, y, angle) o algo asi vos fijate
					//break
		
		case 1: //se recibe que se quiere mover un gusano
				//esto en el proxy del client no estaria
				unsigned int gusano_number = this->receive_unsigned_int(socket);
				int direction = this->receive_int(socket);
				turn.move_gusano(gusano_number, direction);
				break;
		}
}

const unsigned char Proxy::receive_char(Socket& socket){
	char received;
	socket.receive_(&received, ONEBYTE);
	return received;
}

const float Proxy::receive_float(Socket& socket){
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
}






