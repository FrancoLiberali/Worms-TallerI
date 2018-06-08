#ifndef VIGACHICA_H
#define VIGACHICA_H
#include "viga.h"
#include <yaml-cpp/yaml.h>

class VigaChica : public Viga
{
public:
    // Crea una viga chica.
    VigaChica(int angulo);
    // Escribe sobre un stream de yaml.
    void escribir(YAML::Emitter& out) const;
    // Destruye la viga.
    ~VigaChica();
};

#endif // VIGACHICA_H
