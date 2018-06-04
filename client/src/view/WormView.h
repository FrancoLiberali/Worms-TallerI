#ifndef _WORM_VIEW_
#define _WORM_VIEW_ 

#include "Window.h"
#include "Animation.h"
#include "WormState.h"
#include <map>

#define ALIVE = 0;
#define DEAD = 1;

class WormView {
private:
	Window* window;
	int id, x, y, dir, angle;
	WormState state;
	Animation anime;
	std::map<WormState, Animation*> animations; 
public:
	WormView();
	~WormView();
	void load(int x, int y, Window* window);
	void setPos(int x, int y);
	void update();
	void changeState(WormState newState);
	void setDirection(int dir);
	void setAngle(int angle);	
};

#endif