#include <iostream>
#include <string>
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "view/mainView.h"
#include "controller/EventHandler.h"
#include "common/Queue.h"
#include "controller/Event.h"
#include "ProxyClient.h"
#include "GameBuilder.h"
#include "model/GameControllerProxy.h"
#include "model/Model.h"
#include "controller/Controller.h"
#include "view/newView/Boot.h"
#include "common/socket.h"
#include "common/socket_error.h"


#define W_WIDHT 800
#define W_HEIGHT 600

#include <iostream>

int main(int argc, char *argv[]){
	std::string name;
	std::string host;
	std::string port;

	printf("Ingrese su nombre: ");
	getline(std::cin,name);
	
	printf("Ingrese la IP del server: ");
	getline(std::cin,host);

	printf("Ingrese el puerto de conexion : ");
	getline(std::cin,port);

	Socket socket;
	try{
		socket.connect_(host.c_str(),port.c_str());
	} catch(SocketError& e){
		//std::cout<<e.what()<<std::endl;
		return 0;
	}

	ProxyClient proxy(std::move(socket));

	//cargamos todas las texturas y el screen principal
	Boot boot;
	boot.init();
	//cola de comandos a enviar
	Queue<ClientCommand*> commandsQueue;
	ClientCommandSender commmandSender(proxy, commandsQueue);
	commmandSender.start();

	EventHandler ehandler;

	mainView clientView(ehandler, boot.getScreen());
	ehandler.setView(&clientView);

	GameControllerProxy gcp(commandsQueue);

	Model model;
	model.setGameControllerProxy(&gcp);
	model.setNamePlayer(name);

	//cola de eventos a recibir
	Queue<Event*> eventQueue; 
	ClientEventReceiver eventReceiver(proxy, eventQueue, model, clientView);
	eventReceiver.start();

	model.setComunnication(&commmandSender, &eventReceiver);

	Controller controller(model, clientView);
	//Game loop
	int step = 0;
	while(clientView.isOpen()){
		SDL_Event e;
		SDL_PollEvent(&e);
		controller.handle(e);
		//desencolo los eventos del server
		while (!eventQueue.empty()){
			ehandler.add(eventQueue.pop());
		}
		clientView.update();
		step++;
	}
	proxy.close();
	commandsQueue.push(nullptr);
	eventReceiver.stop();
	commmandSender.join();
	eventReceiver.join();
	return 0;
}
