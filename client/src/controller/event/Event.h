#ifndef _EVENT_H
#define _EVENT_H

class mainView;
#include "../../view/mainView.h"
#include "../../model/Model.h"

class Model;

class Event {
protected:
	mainView* view;
	Model* model;
public:
	void setView(mainView* view);
	void setModel(Model* model);
	virtual void process() = 0;
	virtual ~Event(){};
};

#endif