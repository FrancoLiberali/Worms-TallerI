#include <string>

#ifndef __SOCKET_H__
#define __SOCKET_H__

class Socket{
	private:
		int file_descrip;
		
		explicit Socket(int file_descriptor);
		
	public:
	// perdon por los nombres de las funciones pero sino 
	// no tenian el '_' en el cpp al hacer por ejemplo
	// bind(...) se me intentaba llamar a estos metodos 
	// en lugar de las funciones de la libreria de sockets
	// generandome error de compilacion ya que las firmas 
	// no correspondian con los argumentos
		
		// Crea el socket o lanza SocketError en caso de no ser posible.
		Socket();
		
		// Crea el socket en base al moviento de otro 
		// o lanza SocketError en caso de no ser posible.
		Socket(Socket&& other);
		
		~Socket() noexcept;
		
		// Calla todas las conexiones del socket
		void shutdown_();
		
		// Enlaza al socket como servidor a un puerto port del localhost.
		// Post: El socket fue enlazado o lanza SocketError en caso de error.
		void bind_(const char* port);
		
		// Acepta una conexion con un cliente.
		// Pre: el socket fue bindeado a algun puerto del local host.
		// Post:  Devuelve un Socket activo que permite comunicacion 
		// con el cliente o lanza SocketError en caso de error.
		Socket accept_();
		
		// Intenta conectar el socket a hostip:port, esperando 
		// que el mismo lo acepte 
		// Post: Conecta al socket con el servidor permitiendo comunicacion con el
		// o lanza SocketError en caso de error de conexion
		void connect_(const char* hostip, const char* port);
		
		// Envia un msg de len bytes de largo al socket con el que se este conectado
		// Pre: el socket es activo tal que permite comunicaciones.
		// Post: el msg fue enviado correctamente,
		// o lanza SocketError en caso de error de conexion. 
		void send_(const char* msg, size_t len);
		
		
		// Recibe un mensaje de len bytes de largo desde el socket con 
		// el que se este conectado dejando esa informacion en buff.
		// Pre: el socket es  activo tal que permite comunicaciones
		// Post: buff contiene el mensaje recibido o lanza
		// SocketError en caso de error de conexion.
		void receive_(char* buff, size_t len);
		
		Socket(const Socket& other) = delete;
		Socket& operator= (const Socket& other) = delete;
};
#endif
		
		
