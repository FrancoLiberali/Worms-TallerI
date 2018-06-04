#include <iostream>
#include "socket.h"

#define EXIT 'q'

int main(int argc, char** argv){
	if (argc < 3){
		return 1;
	}
	try {
		Socket socket;
		socket.connect_(argv[1], argv[2]);
	
		char entry;
		while (entry != EXIT){
			entry = std::cin.get();
		}
	} catch(std::exception& e){
		std::cout << e.what() << '\n';
	}
	return 0;
}
