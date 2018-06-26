#include "Util.h"

SDL_Color Util::getColor(int id)
{
	SDL_Color color;

    switch (id){
		case 0: color = {255,0,0}; return color;
		case 1: color = {255,102,0}; return color;
		case 2: color = {0,102,255}; return color;
		case 3: color = {0,204,0}; return color;
		case 4: color = {153,153,102}; return color;
        case 5: color = {204,51,153}; return color;
		case 6: color = {255,255,255}; return color;
		case 7: color = {0,0,0}; return color;
		case 8: color = {255,204,102}; return color;
		case 9: color = {0,255,204}; return color;
	}
}

void Util::getDimentionTexture(SDL_Texture* texture, int* w, int* h){
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}
