#ifndef _TEXTURE_MANAGER_H
#define _TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include <string>

#include "../exception/SdlException.h"
#include "../exception/GameException.h"
#include "Camera.h"

/**
* @class TextureManager
* Emplea el patrón Singletón y es el que contiene todas las texturas a usar
* contiene toda la lógica del dibujado de SDL
*/
class TextureManager {
private:
    Camera camera;
    std::map<std::string, SDL_Texture*> texture_map;
    int screenWidth;
	int screenHeight;
    bool intersectRects(SDL_Rect one, SDL_Rect two);
public:
    TextureManager();
    ~TextureManager();
    static TextureManager & Instance(){
			static TextureManager theTextureManager;
			return theTextureManager;
	}

    void init(int w, int h);
    
    bool load(std::string fileName,std::string id, SDL_Renderer* pRenderer);

    void draw(std::string id, int x, int y, double angle, SDL_Renderer* pRenderer
        , SDL_RendererFlip flip = SDL_FLIP_NONE, int d_w = 0, int d_h = 0);

	void drawFrame(std::string id, int x, int y, double angle, int width, int
					height, int currentRow, int currentFrame, SDL_Renderer*
					pRenderer,bool grey = false, SDL_RendererFlip flip = SDL_FLIP_NONE);

    void setScreenSize(int w, int h);

    SDL_Texture * getTexture(std::string imageId);

    int getScreenWidth() { return this->screenWidth;}

	int getScreenHeight() { return this->screenHeight;}

	void drawFillRect(SDL_Renderer*	pRenderer, SDL_Rect & rect, SDL_Color color);

    Camera& getCamera();
};

#endif