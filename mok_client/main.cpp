#include <iostream>
#include "socket.h"
#include "mok_proxy.h"
#include "mok_receiver.h"
#include <string>

#define EXIT 'q'

int main(int argc, char** argv){
	if (argc < 3){
		return 1;
	}
	try {
		Socket socket;
		socket.connect_(argv[1], argv[2]);
		MokProxy proxy(socket);
		char name_c[20];
		std::cin.get(name_c, 20, '\n');
		std::string name(name_c);
		proxy.sendName(name);
		MokReceiver receiver(proxy);
		receiver.start();
	
		char entry;
		while (entry != EXIT){
			entry = std::cin.get();
			proxy.send(entry);
		}
		receiver.stop();
		receiver.join();
	} catch(std::exception& e){
		std::cout << e.what() << '\n';
	}
	return 0;
}
