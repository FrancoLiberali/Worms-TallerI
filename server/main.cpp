#include "server.h"
#include <syslog.h>
#include <iostream>
#include "thread.h"
#include <dirent.h>

#define PORT 1
#define CANT_ARGC 2
#define INVALID_ARGS "Error: argumentos invalidos.\n"
#define MAPS_ERROR "No se hayo el directorio de mapas\n"
#define CRIT_ERROR "[Crit] ​Error: %s"
#define NO_MAPS "No hay ningun mapa disponible"
#define MAPS_PATH "../maps"
#define YAML_LEN 5
#define EXIT 'q'

int main(int argc, char* argv[]){
	if (argc != CANT_ARGC){
		syslog(LOG_CRIT, CRIT_ERROR, INVALID_ARGS);
		return 0;
	}
	std::vector<std::string> maps;
	struct dirent *map;
    DIR* maps_dir;
    maps_dir = opendir(MAPS_PATH);
    if (maps_dir == NULL) {
		syslog(LOG_CRIT, CRIT_ERROR, MAPS_ERROR);
		return 0;
    }
    while ((map = readdir(maps_dir))){
		std::string name(map->d_name);
		if (name.length() > YAML_LEN){
			maps.push_back(name);
		}
	}
    closedir(maps_dir);
    if (maps.size() == 0) {
		syslog(LOG_CRIT, CRIT_ERROR, NO_MAPS);
		return 0;
    }
	std::mutex syslog_mutex;
	try{
		Server server(argv[PORT], syslog_mutex, maps);
		server.start();
		char entry = 0;
		while (entry != EXIT){
			entry = std::cin.get();
		}
		server.stop();
		server.join();
		return 0;
	} catch(const std::exception& e){
		std::lock_guard<std::mutex> lock(syslog_mutex);
		syslog(LOG_CRIT, CRIT_ERROR, e.what());
		return 0;
	}
}
