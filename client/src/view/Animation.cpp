#include "Animation.h"

Animation::Animation(){}

void Animation::load(const std::string& path, Window& window){
		spriteTexture.loadFromFile(path, window);
}

void Animation::configSprite(){
	//sprite clips
	int w = this->spriteTexture.getWidth();
	int h = this->spriteTexture.getHeight()/frames;

	for (int i = 0; i < frames; ++i){
		int x = h*i;
		SDL_Rect clip = {0, x, w, h};
		spriteClips.push_back(clip);
	}
}

void Animation::render(){
	SDL_Rect* currentClip = &spriteClips[this->currFrame];
	this->spriteTexture.render(x-currentClip->w/2, y-currentClip->h/2, 0, currentClip);
	this->currFrame++;
	if(currFrame >= frames)
		this->currFrame = 0;
}

void Animation::setPos(int x, int y){
	this->x = x; this->y = y;
}


void Animation::setFrames(int frames){
	this->frames = frames;
	this->configSprite();
}
