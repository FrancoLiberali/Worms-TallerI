#ifndef _EVENT_H
#define _EVENT_H

class View;
#include "../view/View.h"

class Event {
protected:
	View* view;
public:
	void setView(View *view);
	virtual void process() = 0;
	virtual ~Event(){};	
};


#endif