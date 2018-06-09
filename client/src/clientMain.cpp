#include <iostream>
#include <string>
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "view/mainView.h"
#include "controller/EventHandler.h"
#include "common/Queue.h"
#include "controller/Event.h"
#include "ProxyClient.h"
#include "model/GameControllerProxy.h"
#include "model/Model.h"
#include "controller/Controller.h"
#include "view/newView/Boot.h"


#define W_WIDHT 800
#define W_HEIGHT 600

#include <iostream>


int main(int argc, char *argv[])
{
	//Validamos que se conecte correctamente
	std::string socket = "socket.txt";

	ProxyClient proxy(socket);


	//agregar protoclo para empezar el juego, id mapa , etc

	/*****INICIO GAME ****/
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
	Model model(gcp);


	//cola de eventos a recibir
	Queue<Event*> eventQueue;
	ClientEventReceiver eventReceiver(proxy, eventQueue, socket, model);
	eventReceiver.start();

	Controller controller(model, clientView);
	//Game loop
	int step = 0;
	while(clientView.isOpen()){
		SDL_Event e;
		SDL_WaitEvent(&e);
		//std::cout<<"Se intrudujo un evento" << std::endl;
		controller.handle(e);

		//desencolo los eventos del server
		while (!eventQueue.empty()){
			ehandler.add(eventQueue.pop());
		}
		clientView.update();
		step++;
	}
	commandsQueue.push(nullptr);
	eventReceiver.stop();
	commmandSender.join();
	eventReceiver.join();
	//std::cout<<"AQUI"<<std::endl;
	return 0;
}
