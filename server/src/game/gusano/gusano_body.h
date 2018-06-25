#ifndef __GUSANO_BODY_H__
#define __GUSANO_BODY_H__

#include "Box2D/Box2D.h"
#include "game/Box2d_elements/user_data.h"

#define FOOT_SENSOR_DATA 1
#define HEAD_SENSOR_DATA 2

class GusanoBody{
	private:
		b2World& world;
		b2Body* body;
		
		//las datas son punteros que los cuerpos del mundo de simulacion
		// tienen asociados para poder reconocerlos a la hora de un contacto
		// y poder llamar a sus metodos. Para mas info ver contact_listener
		int* foot_sensor_data;
		int* head_sensor_data;
	
	public:
		GusanoBody(b2World& world_e, float x, float y, float angle, UserData* user_data);
		
		~GusanoBody();
		
		GusanoBody(GusanoBody&& other);
		GusanoBody& operator=(GusanoBody&& other);
		
		void setUserData(UserData* user_data);
		
		// Devuelve el vector posicion del cuerpo del gusano
		b2Vec2 GetPosition();
		
		// Devuelve el angulo en el que se encuentra el cuerpo del gusano.
		float32 GetAngle();
		
		// Devuelve la velocidad en la que se enceuntra el cuerpo del gusano
		b2Vec2 getLinearVelocity();
		
		// Cancela cualquier tipo de movimiento que el gusano
		// este realizando si este es invalido a nivel de jugabilidad.
		void cancelMovement();
		
		// Mueve el cuerpo de un gusano de la direccion dir
		void move(int dir);
		
		// Setea la velocidad al cuerpo del gusano 
		// para que este salte un metro hacia adelante
		// y medio metro hacia arriba.
		void jump(int dir);
		
		// Setea la velocidad al cuerpo del gusano 
		// para que este salte hacia atras 0.2 y 1.2 metros de alto
		void backJump(int dir);
		
		// Hace que el gusano se vea afectado por la gravedad
		void setGravity();
		
		// Aplica al cuerpo del gusano fuerzas repulsivas respondientes a una explosion.
		void applyExplotion(b2Vec2 apply_point, b2Vec2 impulse);
		
		// Teletransporta al cuerpo del gusano a la nueva posicion
		// Pre: la posicion esta vacia.
		void teleport(b2Vec2 new_position, float angle);
		
};

#endif
