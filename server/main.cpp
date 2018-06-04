#include "game.h"
#include "socket.h"
#include "protected_queue.h"
#include "proxy.h"
#include "fake_proxy/mok_proxy.h"
#include <iostream>
#include "receiver.h"

int main(int argc, char** argv) {
	if (argc < 2){
		return 1;
	}
	Socket socket;
	socket.bind_(argv[1]);
	Socket active = socket.accept_();
	//Proxy proxy(active);
	MokProxy proxy;
	
	ProtectedQueue queue;
	Receiver receiver(proxy, queue);
	Game game(active, queue);
	receiver.start();
	game.play();
	receiver.stop();
	receiver.join();
	return 0;
}
