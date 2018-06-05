#include <iostream>
#include <string>
#include "controller/ClientEventReceiver.h"
#include "controller/ClientCommandSender.h"
#include "view/View.h"
#include "controller/EventHandler.h"
#include "common/Queue.h"
#include "controller/Event.h"
#include "ProxyClient.h"
#include "model/GameControllerProxy.h"
#include "model/Model.h"
#include "controller/Controller.h"


#define W_WIDHT 800
#define W_HEIGHT 600

int main(int argc, char const *argv[])
{
	//Le pasamos el archivo a leer, deberia ser el socket
	std::string socket = "socket.txt";

	ProxyClient proxy(socket);

	//cola de eventos a recibir
	Queue<Event*> eventQueue;
	ClientEventReceiver eventReceiver(proxy, eventQueue, socket);
	eventReceiver.start();
	
	//cola de comandos a enviar
	Queue<ClientCommand*> commandsQueue;
	ClientCommandSender commmandSender(proxy, commandsQueue);
	commmandSender.start();

	EventHandler ehandler;

	View clientView(ehandler,W_WIDHT, W_HEIGHT);
	ehandler.setView(&clientView);

	GameControllerProxy gcp(commandsQueue);
	Model model(gcp);

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

	return 0;
}
