#ifndef _EVENT_H
#define _EVENT_H

class mainView;
#include "../view/mainView.h"
#include "../model/Model.h"

class Event {
protected:
	mainView* view;
	Model* model;
public:
	void setView(mainView *view);
	virtual void process() = 0;
	virtual ~Event(){};	
};

#endif