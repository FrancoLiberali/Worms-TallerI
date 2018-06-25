#ifndef __SPRITE_CONFIGURATOR_H__
#define __SPRITE_CONFIGURATOR_H__

#include <string>
#include <sstream>
#include <map>
#include "../view/Sprite.h"
#include "../exception/GameException.h"
/*
*@class SpriteConfigurator
* Usa el patrón singletón, es un contenedor de todos los Sprite.
*/

class SpriteConfigurator{
private:
	std::map<std::string, Sprite> sprite_map;
public:
	
	SpriteConfigurator();

	static SpriteConfigurator & Instance(){
			static SpriteConfigurator theInstance;
			return theInstance;
	}
	//Agrega un sprite al diccionario, para ello recive todos lo necesario para la creación de un Sprite
	//Lanza GameException si hay un problema se añade dos veces el mismo sprite
	void add(std::string imageId, int width, int height, int rows, int countSleepFrame, int initFrame = 0);
	//Retorna un sprite dado un Id.
	//Lanza GameException en caso de no existir el id.
	Sprite get(std::string imageId);

	~SpriteConfigurator();
};



#endif 