#ifndef VIGA_GRANDE_H
#define VIGA_GRANDE_H
#include <QGraphicsItem>
#include <yaml-cpp/yaml.h>
#include "viga.h"

class VigaGrande : public Viga
{
public:
    // Construye viga.
    VigaGrande(int angulo);
    // Escribe sobre un stream de yaml.
    void escribir(YAML::Emitter& out) const;
    // Destruye la viga.
    ~VigaGrande();
};

#endif // VIGA_GRANDE_H
