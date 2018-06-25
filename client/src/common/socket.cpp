#define _POSIX_C_SOURCE 200112L

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include "../exception/socket_error.h"
#include "socket.h"

#define NO_CREATED -1
#define MAX_CLIENT_QUEUE 10

Socket::Socket() : file_descrip(socket(AF_INET, SOCK_STREAM, 0)){
	if (this->file_descrip == NO_CREATED){
		throw SocketError("No se puedo crear el socket.");
	}
}

Socket::Socket(int file_descriptor) : file_descrip(file_descriptor){
	if (this->file_descrip == NO_CREATED){
		throw SocketError("No se puedo crear el socket.");
	}
}

Socket::Socket(Socket&& other) : file_descrip(other.file_descrip){
	other.file_descrip = 0;
}

Socket::~Socket(){
	if (this->file_descrip){ //por si fue movido o cerrado anteriormente
		shutdown(this->file_descrip, SHUT_RDWR);
		close(this->file_descrip);
	}
}

void Socket::shutdown_(){
	if (this->file_descrip){ //por si fue movido
		shutdown(this->file_descrip, SHUT_RDWR);
	}
}

void Socket::bind_(const char* port){
	struct addrinfo hints;
	struct addrinfo *result, *addr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;        //IPv4 
	hints.ai_socktype = SOCK_STREAM;  //TCP
	hints.ai_flags = AI_PASSIVE;	  //SERVER
	
	int error = 0;
	error = getaddrinfo(NULL, port, &hints, &result);
	if (error) { 
		throw SocketError("falla en getaddrinfo con port: %s. %s.", 
		port, gai_strerror(error));
	}
	
	// Activamos la opcion de Reusar la Direccion en caso de que esta
	// no este disponible por un TIME_WAIT
	int val = 1;
	error = setsockopt(this->file_descrip, 
		SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	if (error == -1) {
		freeaddrinfo(result);
		throw SocketError("falla en setsockopt.");
	}
	
	bool linked = false;
	for (addr = result; addr != NULL && linked == false; addr = addr->ai_next){
		error = bind(this->file_descrip, addr->ai_addr, addr->ai_addrlen);
		if (error != -1) {
			linked = true;
		}
	}
	freeaddrinfo(result);
	if (!linked){
		throw SocketError(
		"No se puedo conectar al port: %s con ninguna direccion.", port);
	}
	
	error = listen(this->file_descrip, MAX_CLIENT_QUEUE);
	if (error == -1) {
		throw SocketError(
		"No se puedo hacer que la cola de espera maxima de clientes sea %i.",
		 MAX_CLIENT_QUEUE);
	}
}

Socket Socket::accept_(){
	int new_file_descrip = accept(this->file_descrip, NULL, NULL);
	Socket new_socket(new_file_descrip);
	return (std::move(new_socket));
}

void Socket::connect_(const char* hostip, const char* port){
	struct addrinfo hints;
	struct addrinfo *result, *addr;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;        //IPv4 
	hints.ai_socktype = SOCK_STREAM;  //TCP
	hints.ai_flags = 0;	  			  //CLIENT
	
	int error = 0;
	error = getaddrinfo(hostip, port, &hints, &result);
	if (error) { 
		throw SocketError("falla en getaddrinfo con hostip: %s, port: %s.",
		hostip, port);
	}
	
	bool connected = false;
	for (addr = result; addr != NULL && connected == false; addr = addr->ai_next) {
		error = connect(this->file_descrip, addr->ai_addr, addr->ai_addrlen);
		if (error != -1) {
			connected = true;
		}
	}
	freeaddrinfo(result);
	if (!connected){
		throw SocketError(
		"No se puedo conectar al hostip: %s, port: %s con ninguna direccion.",
		hostip, port);
	}
}

void Socket::send_(const char* msg, size_t len){
	size_t bytes_sent = 0, rem_len;
	int send_this_iteration = 0;
	while (bytes_sent < (len * sizeof(char))) {
		rem_len = (len * sizeof(char)) - bytes_sent;
		send_this_iteration = send(this->file_descrip, 
					&msg[bytes_sent], rem_len, MSG_NOSIGNAL);
		if (send_this_iteration <= 0) {		  // socket error or closed
			throw SocketError(
			"Solo se pudieron enviar %i bytes del mensaje %s.", 
			bytes_sent, msg);
		}else {
			bytes_sent += send_this_iteration;
		}
	}
}

void Socket::receive_(char* buff, size_t len){
	size_t bytes_received = 0;
	size_t rem_len;
	int received_this_it = 0;
	while (bytes_received < (len * sizeof(char))) {
		rem_len = (len * sizeof(char)) - bytes_received;
		received_this_it = recv(this->file_descrip, 
					&buff[bytes_received], rem_len, 0);

		if (received_this_it <= 0) {
			throw SocketError(
			"Solo se pudieron recibir %i bytes cuando se esperaban %i bytes.", 
			bytes_received, len);
		}else {
			bytes_received += received_this_it;
		}
	}
}
