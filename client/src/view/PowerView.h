#ifndef _POWER_VIEW_H_
#define _POWER_VIEW_H_

#include "TextureManager.h"
#include "SdlScreen.h"
#include "TextView.h"

class PowerView{
private:
	TextView label;
	SDL_Rect rect;
	bool ballow;
    SdlScreen& screen;
    int posx, posy;
public:
	PowerView(SdlScreen& screen);
    void setPos(int x, int y);
	void clean();
	void update();
	void change();
	void draw();
	void allow();
	void deny();
};

#endif