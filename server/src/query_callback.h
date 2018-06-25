#include "Box2D/Box2D.h"

#ifndef __QUERY_CALLBACK_H__
#define __QUERY_CALLBACK_H__

class QueryCallback : public b2QueryCallback{
	private:
		bool desocuped = true;
	public:
		// Callback de la funcionalidad Query de BOX2d que permite
		// hallar todos los cuerpos en una determinada seccion del mapa
		QueryCallback(){}
		
		// Se reporta el hayasgo de un cuerpo en la posicion del Query
		// por lo que la posicion se encuentra ocuapada
		bool ReportFixture(b2Fixture* fixture){
			this->desocuped = false;
			return false;
		}
		
		// Devuelve si la seccion del Query estaba ocupada o no
		bool isDesocuped(){
			return this->desocuped;
		}
};

#endif
