#include "validadordemapa.h"

#define MIN_GUSANOS 2
#define MIN_VIGAS 1
#define MIN_ARMAS_DISP 1

ValidadorDeMapa::ValidadorDeMapa() {}

 bool ValidadorDeMapa::operator() (const Registro& registro)
 {
 	return (registro.get_cant_gusanos() >= MIN_GUSANOS) &&
 			(registro.get_cant_vigas() >= MIN_VIGAS)   &&
 			(registro.get_armas_validas().size() >= MIN_ARMAS_DISP);
 }

ValidadorDeMapa::~ValidadorDeMapa() {}