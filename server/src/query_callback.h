#include "Box2D/Box2D.h"

#ifndef __QUERY_CALLBACK_H__
#define __QUERY_CALLBACK_H__

class QueryCallback : public b2QueryCallback{
	private:
		bool desocuped = true;
	public:
		QueryCallback(){}

		bool ReportFixture(b2Fixture* fixture){
			this->desocuped = false;
			return false;
		}
		
		bool isDesocuped(){
			return this->desocuped;
		}
};

#endif
