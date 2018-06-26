#include "SpriteConfigurator.h"


SpriteConfigurator::SpriteConfigurator(){
}

SpriteConfigurator::~SpriteConfigurator(){
}

void SpriteConfigurator::add(std::string imageId, int width, int height, int rows, int countSleepFrame, int initFrame){
	
	if (sprite_map.find(imageId) != sprite_map.end()){
		std::string msg = "SpriteConfigurator: El sprite id: ";
		msg += imageId; msg += " ya existe";
		throw GameException(msg.c_str());
	} 
	
	Sprite aSprite(imageId, width, height, rows, countSleepFrame, initFrame);
	sprite_map[imageId] = aSprite;
}


Sprite SpriteConfigurator::get(std::string imageId) {
	if (sprite_map.find(imageId) != sprite_map.end())
		return sprite_map[imageId];

	std::string msg = "SpriteConfigurator: no se encontro encontro el sprite id: ";
	msg += imageId;
	throw GameException(msg.c_str());
}
