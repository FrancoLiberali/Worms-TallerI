#include "Box2D/Box2D.h"
#include <vector>
#include "user_data.h"
#include "multiple_proxy.h"
#include <map>

#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

class Projectile {
	protected:
		b2World& world;
		const int number;
		const int direction;
		b2Body* body;
		const int damage;
		const int radius;
		std::vector<int>& to_remove;
		MultipleProxy& proxy;
		const UserData user_data;
		
	public:		
		// Crea un proyectil, creando su cuerpo fisico
		Projectile(b2World& world_entry, int number, float x, float y, int direction, float angle, float vel,
				   int damage_e, int radius_e, int type, std::vector<int>& to_remove_e, MultipleProxy& proxy_e);
		
		~Projectile();
		
		// Explota un proyectil generando una fuerza en todos los gusanos cercanos.
		virtual void exploit();
		
		// Actualiza el proyectil enviando los mensajes correspondientes
		virtual void update(float wind);
		
		// Aplica al cuerpo del proyectil la fuerza correspondiente al viento
		void setWindForce(float wind);
		
		// Aplica al cuerpo del proyectil la fuerza correspondiente al drag con el aire
		void setDragForce(float missile_widht);
		
		// Devuelve la posicion del proyetil
		b2Vec2 GetPosition();
		
		// Devuelve el angulo del proyectil
		float32 GetAngle();
		
		// Destruye el proyectil, causando una explosion pero que no hace danio ni fuerza
		// a los cercanos
		void destroy();
};

#endif
