#include "server.h"
#include <syslog.h>
#include <iostream>
#include "thread.h"

#define PORT 1
#define CANT_ARGC 2
#define INVALID_ARGS "Error: argumentos invalidos.\n"
#define CRIT_ERROR "[Crit] ​Error: %s"
#define EXIT 'q'

int main(int argc, char* argv[]){
	if (argc != CANT_ARGC){
		syslog(LOG_CRIT, CRIT_ERROR, INVALID_ARGS);
		return 0;
	}
	std::mutex syslog_mutex;
	try{
		Thread* server = new Server(argv[PORT], syslog_mutex);
		server->start();
		char entry = 0;
		while (entry != EXIT){
			entry = std::cin.get();
		}
		server->stop();
		server->join();
		delete server;
		return 0;
	} catch(const std::exception& e){
		std::lock_guard<std::mutex> lock(syslog_mutex);
		syslog(LOG_CRIT, CRIT_ERROR, e.what());
		return 0;
	}
}
