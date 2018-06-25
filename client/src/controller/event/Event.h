#ifndef _EVENT_H
#define _EVENT_H

class mainView;
#include "../../view/mainView.h"
#include "../../model/Model.h"

class Model;

/*@ class: Event
* Clase abstracta que representa a todos los eventos que pueden alterar al cliente.
* cualquier nuevo evento deberá heredar de esta clase para ser agregada.
*/
class Event {
protected:
	mainView* view;
	Model* model;
public:
	void setView(mainView* view);
	void setModel(Model* model);

	//método virtual que realiza los efectos del evento.
	virtual void process() = 0;
	virtual ~Event(){};
};

#endif