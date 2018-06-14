#include "SpriteConfigurator.h"


SpriteConfigurator::SpriteConfigurator(){
}

SpriteConfigurator::~SpriteConfigurator(){
}

void SpriteConfigurator::add(std::string imageId, int width, int height, int rows, int countSleepFrame, int initFrame){
	
	if (sprite_map.find(imageId) != sprite_map.end()){
		std::stringstream msg;
		msg<<"SpriteConfigurator: El sprite id: "<<imageId<< "ya existe";
		throw GameException(msg.str());
	} 
	
	Sprite aSprite(imageId, width, height, rows, countSleepFrame, initFrame);
	sprite_map[imageId] = aSprite;
}


Sprite SpriteConfigurator::get(std::string imageId) {
	if (sprite_map.find(imageId) != sprite_map.end())
		return sprite_map[imageId];

	std::stringstream msg;
	msg<<"SpriteConfigurator: no se encontro encontro el sprite id: "<<imageId;
	throw GameException(msg.str());
}
