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

//argv[1]=ip argv[2]=port
int main(int argc, char *argv[])
{
	//Validamos que se conecte correctamente

	Socket socket;
	try{
		socket.connect_(argv[1],argv[2]);
	} catch(SocketError& e){
		std::cout<<e.what()<<std::endl;
		return 0;
	}

	ProxyClient proxy(std::move(socket));

	//agregar protoclo para empezar el juego, id mapa , etc

	//Recibo el numero de jugador
	char cod = proxy.receiveChar();
	std::cout <<"Cod " << (int)cod <<std::endl;
	int idJugador = proxy.receiveInt();
	std::cout << "idJugador" << idJugador <<std::endl;
	if (idJugador == 1){
		//envio id mapa y numero de jugadores
		int idMapa = 1;
		int numPlayers = 1;
		proxy.sendChar(0);
		proxy.sendInt(idMapa);
		proxy.sendInt(numPlayers);
	}

	Boot boot;
	boot.init();

	//GameBuilder builder(proxy);
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
	ClientEventReceiver eventReceiver(proxy, eventQueue, model);
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
	proxy.close();
	commandsQueue.push(nullptr);
	eventReceiver.stop();
	commmandSender.join();
	eventReceiver.join();
	//std::cout<<"AQUI"<<std::endl;
	return 0;
}
