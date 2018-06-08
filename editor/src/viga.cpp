#include "viga.h"

Viga::Viga(int angulo) : angulo(angulo), eliminado(false) {}

void Viga::set_eliminado()
{
    this->eliminado = true;
}

bool Viga::esta_eliminado()
{
    return this->eliminado;
}

YAML::Emitter& operator<<(YAML::Emitter& out, const Viga& obj)
{
    obj.escribir(out);
    return out;
}
