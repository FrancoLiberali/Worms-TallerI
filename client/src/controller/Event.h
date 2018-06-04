#ifndef _EVENT_H
#define _EVENT_H

class View;
#include "../view/View.h"
#include "../model/Model.h"

class Event {
protected:
	View* view;
	Model* model;
public:
	void setView(View *view);
	virtual void process() = 0;
	virtual ~Event(){};	
};

#endif