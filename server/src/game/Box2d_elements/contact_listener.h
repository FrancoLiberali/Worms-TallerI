#include "Box2D/Box2D.h"
#include "game/gusano/gusano.h"
#include "game/weapons/projectile.h"
#include "game/Box2d_elements/user_data.h"
#include <iostream>

#ifndef __CONTACT_LISTENER_H__
#define __CONTACT_LISTENER_H__

class ContactListener : public b2ContactListener{
	private:
		// Cheque si el dataA corresponde a un delimiter
		// y si el dataB corresponde a un proyectil o a un gusano
		// es destruido.
		void checkDelimiter(UserData* dataA, UserData* dataB);
		
		// Chequea si el fixture_data corresponde a un foot sensor.
		// De ese asi, accede al gusano duenio de ese foot sensor
		// y si el angulo del otro objeto other_angle
		// se encuentra entre dos valores establecidos
		// si el type es BEGIN le avisa que comenzo un contacto de pie
		// de lo contario, avisa que termino un contacto de pie.
		void checkFootSensor(b2Fixture* fixture, void* fixture_data, float other_angle, int type);
		
		// Chequea si el fixture_data corresponde a un head sensor.
		// De ese asi, accede al gusano duenio de ese head sensor
		// y si el angulo del otro objeto other_angle
		// se encuentra entre dos valores establecidos
		// si el type es BEGIN le avisa que comenzo un contacto de cabeza
		// de lo contario, avisa que termino un contacto de cabeza.
		void checkHeadSensor(b2Fixture* fixture, void* fixture_data, int type);
		
		// Chequea si el dataA es un proyetil
		// y si el dataB no es un delimitador, lo hace explotar.
		void checkProjectile(UserData* dataA, UserData* dataB);
		
		// Chequea si el dataA es un gusano inactivo,
		// y si el dataB es un gusano o un proyectil
		// cancela todas las fuerzas que este sufriendo
		// el gusano inactivo.
		void checkGusano(UserData* dataA, UserData* dataB);
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
