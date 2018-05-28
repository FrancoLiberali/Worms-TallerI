#ifndef _WORM_VIEW_
#define _WORM_VIEW_ 

#include "Window.h"
#include "Animation.h"
#define ALIVE = 0;
#define DEAD = 1;

class WormView {
private:
	Window* window;
	int id;
	int x, y;
	int state;
	Animation anime;
public:
	WormView();
	void load(int x, int y, Window* window);
	void setPos(int x, int y);
	void update();
	
};

#endif