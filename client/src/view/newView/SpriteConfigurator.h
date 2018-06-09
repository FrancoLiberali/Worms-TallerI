#ifndef __SPRITE_CONFIGURATOR_H__
#define __SPRITE_CONFIGURATOR_H__

#include <string>
#include <sstream>
#include <map>
#include "Sprite.h"
#include "GameException.h"

class SpriteConfigurator{
private:
	// Contains all texture
	std::map<std::string, Sprite> sprite_map;
public:
	
	SpriteConfigurator();

	static SpriteConfigurator & Instance(){
			static SpriteConfigurator theInstance;
			return theInstance;
	}

	void add(std::string imageId, int width, int height, int rows, int countSleepFrame);
	
	Sprite get(std::string imageId);

	~SpriteConfigurator();
};



#endif 