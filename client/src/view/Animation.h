#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "Texture.h"
#include <vector>

class Animation {
private:
	LTexture spriteTexture;
	int x, y;
	int currFrame = 0;
	int frames;
	std::vector<SDL_Rect> spriteClips;
	void configSprite();
public:
	Animation();
	void load(const std::string& path, Window& window);
	//~Animation();
	void setPos(int x, int y);
	void render();
	void setFrames(int frames);
};
#endif