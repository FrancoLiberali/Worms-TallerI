#include "arma.h"

Arma::Arma() {}

void Arma::set_tipo(std::string nombre)
{
    this->tipo = nombre;
}
void Arma::set_habilitada()
{
    this->habilitada.assign("si");
}
void Arma::set_deshabilitada()
{
    this->habilitada.assign("no");
}

void Arma::set_municion(std::string municion)
{
    this->municion = municion;
}
std::string Arma::get_tipo() const
{
    return this->tipo;
}
std::string Arma::get_municion() const
{
    return this->municion;
}
bool Arma::esta_habilitada() const
{
    return this->habilitada == "si";
}

YAML::Emitter& operator<<(YAML::Emitter& out, const Arma& arma) {
    out << YAML::BeginMap;
    out << YAML::Key << "tipo";
    out << YAML::Value << arma.tipo;
    out << YAML::Key << "habilitada";
    out << YAML::Value << arma.habilitada;
    out << YAML::Key << "municiones";
    out << YAML::Value << arma.municion;
    out << YAML::EndMap;
    return out;
}
