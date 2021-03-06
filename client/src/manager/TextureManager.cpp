#include "TextureManager.h"
#include "../common/Util.h"

#include <sstream>
#include <iostream>

TextureManager::TextureManager():screenHeight(0),screenWidth(0){}

TextureManager::~TextureManager(){
	std::map<std::string, SDL_Texture*>::iterator iter;
	for (iter = texture_map.begin(); iter!=texture_map.end(); ++iter)
		SDL_DestroyTexture(iter->second);
	texture_map.clear();
}

void TextureManager::init(int w, int h){
	TextureManager::Instance().setScreenSize(w, h);
}

void TextureManager::setScreenSize(int w, int h){
	this->screenWidth = w;
	this->screenHeight = h;
}

bool TextureManager::load(std::string fileName,std::string id, SDL_Renderer* pRenderer){
	SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(pRenderer, tmpSurface);

	SDL_FreeSurface(tmpSurface);
	
	if (newTexture){
		this->texture_map[id]=newTexture;
		return true;
	} 
	std::string  msg = "TextureManager: Imagen NO encontrada: ";
	msg += fileName;
	throw GameException(msg.c_str());
}

void TextureManager::draw(std::string id, int x, int y, double angle, SDL_Renderer* pRenderer
					, SDL_RendererFlip flip, int d_w, int d_h) {
	SDL_Rect srcRect;
	SDL_Rect destRect;
	try {
		SDL_Texture * aTexture = getTexture(id);

		Util::getDimentionTexture(aTexture, &srcRect.w, &srcRect.h);

		srcRect.x = 0;
		srcRect.y = 0;
	
		destRect.w = (d_w > 0) ? d_w : srcRect.w;
		destRect.h = (d_h > 0) ? d_h : srcRect.h;
		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(pRenderer, aTexture, &srcRect,&destRect, angle, 0, flip);
	
	} catch (GameException & e) {
        std::cout << e.what() <<std::endl;
	}
}

void TextureManager::drawFrame(std::string id, int x, int y, double angle, int width, int	height, 
								int currentRow, int currentFrame, 
								SDL_Renderer* pRenderer, bool grey, SDL_RendererFlip flip) 
{	
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect viewPort;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
		
	viewPort.x = 0;
	viewPort.y = 0;
	viewPort.w = this->screenWidth;
	viewPort.h = this->screenHeight;
	try {
		if (grey) SDL_SetTextureColorMod(getTexture(id),100,100,100);
		if (intersectRects(destRect, viewPort)) {
			SDL_RenderCopyEx(pRenderer, getTexture(id), &srcRect,&destRect, angle, 0, flip);
		}
		if (grey) SDL_SetTextureColorMod(getTexture(id),255,255,255);
	} catch (GameException & e) {
        std::cout << e.what() <<std::endl;
	}
}


void TextureManager::drawTexture(SDL_Texture* texture, int x, int y, SDL_Renderer* renderer ){
	int w, h;
	Util::getDimentionTexture(texture, &w, &h);
	SDL_Rect destRect;
	destRect.h = h;
	destRect.w = w;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

SDL_Texture* TextureManager::getTexture(std::string imageId)
{
	if (this->texture_map.find(imageId) != this->texture_map.end())
		return this->texture_map[imageId];
	
	std::string msg = "TextureManager: Texture de ImagenID NO encontrada: ";
	msg +=imageId;
	throw GameException(msg.c_str());
	
}

bool TextureManager::intersectRects(SDL_Rect one, SDL_Rect two){
	SDL_bool hasIntersec = SDL_HasIntersection(&one, &two);
	return (hasIntersec == SDL_TRUE);
}


void TextureManager::drawFillRect(SDL_Renderer*	pRenderer, SDL_Rect & rect, SDL_Color color) {

	SDL_Rect rectDest;

	rectDest.x = rect.x - camera.getX()/screenWidth;
	rectDest.y = rect.y - camera.getY()/screenHeight;
	rectDest.w = rect.w;
	rectDest.h = rect.h;

	SDL_SetRenderDrawColor(pRenderer, color.r, color.g, color.b, color.a); 
	SDL_RenderFillRect(pRenderer, &rectDest);
}

Camera& TextureManager::getCamera(){
	return camera;
}
