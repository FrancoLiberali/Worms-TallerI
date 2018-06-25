#ifndef _POWER_VIEW_H_
#define _POWER_VIEW_H_

#include "TextureManager.h"
#include "SdlScreen.h"
#include "TextView.h"

/*
* @Class PowerView
* Vista de la barra de poder al usar un arma que 
* pueda variar su potencia.
*/
class PowerView{
private:
	TextView label;
	SDL_Rect rect;
	bool ballow;
    SdlScreen* screen;
    int posx, posy;
public:
	PowerView();
	void setScreen(SdlScreen* screen);
    void setPos(int x, int y);
	void clean();
	void update();
	void change();
	void draw();
	void allow();
	void deny();
};

#endif