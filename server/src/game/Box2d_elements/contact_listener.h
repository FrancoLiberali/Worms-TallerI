#include "Box2D/Box2D.h"
#include "game/gusano/gusano.h"
#include "game/weapons/projectile.h"
#include "game/Box2d_elements/user_data.h"
#include <iostream>

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	public:
		//Clase que funciona de callback cuando sucede algun
		// evento en el que el contacto entre dos objetos 
		// se vea afectado
		
		// Se llama cuando empieza contacto entre dos objetos.
		// Si uno de esos objetos es un Delimiter, el otro objeto se destruye.
		// Si alguno de los objetos es un sensor del gusano
		// se avisa al Gusano de este contacto
		// Si alguno de los objetos es un proyectil, el mismo explota.
		void BeginContact(b2Contact* contact);
		
		// Se llama cuando termina el contacto entre dos objetos.
		// Si alguno de esos objetos es un sensor del Gusano
		// se avisa al mismo de la finalizacion se ese contacto.
		void EndContact(b2Contact* contact);
		
		// Funcion que se llama luego de que BOX2D decida
		// que fuerza le debe hacer a dos objetos que
		// se solaparon. Si alguno de estos objetos es un gusano inactivo
		// se cancelan todas las fuerzas sobre este, ya que los Gusanos
		// inactivos no deben sufrir fuerza alguna.
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

#endif
