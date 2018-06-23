#ifndef VALIDADOR_DE_MAPA
#define VALIDADOR_DE_MAPA
#include "registro.h"

class ValidadorDeMapa
{

public:
    // Construye ValidadorDeMapa.
    ValidadorDeMapa();
    // Decide si el mapa es valido o no.
    // Devuelve verdadero en caso de serlo, falso en caso
    // contrario.
    bool operator() (const Registro& registro);
    // Destruye ValidadorDeMapa.
    ~ValidadorDeMapa();
};

#endif // VALIDADOR_DE_MAPA
