#include "registro.h"
#include "gusano.h"
#include "viga.h"
#include <map>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

#define VIDA_DEFAULT 100
#define FONDO_DEFAULT "sky3.png"

Registro::Registro() : nombre_fondo(FONDO_DEFAULT), vida_gusanos(VIDA_DEFAULT) {}

void Registro::agregar_viga(Viga* viga)
{
    this->vigas.push_back(viga);
}

void Registro::agregar_arma(std::string& id, Arma* arma)
{
    this->armas[id] = arma;
}

void Registro::agregar_gusano(Gusano* gusano)
{
   this->gusanos.push_back(gusano);
}

void Registro::actualizar_vigas()
{
    vigas.erase(std::remove_if(begin(vigas), end(vigas),
                               [](Viga* x) { return x->esta_eliminado(); }),
                 end(vigas));
}

void Registro::actualizar_gusano()
{
    gusanos.erase(std::remove_if(begin(gusanos), end(gusanos),
                               [](Gusano* x) { return x->esta_eliminado(); }),
                 end(gusanos));
}

unsigned int Registro::get_cant_gusanos() const
{
    return this->gusanos.size();
}
unsigned int Registro::get_cant_vigas() const
{
    return this->vigas.size();
}

Arma* Registro::get_arma(const std::string& nombre) const
{
    return this->armas.at(nombre);
}

void Registro::set_tam_mapa(float ancho, float alto)
{
    this->tam_mapa.first = ancho;
    this->tam_mapa.second = alto;
}

std::vector<std::string> Registro::get_armas() const
{
    std::vector<std::string> armas;
    for (std::map<std::string, Arma*>::const_iterator it =this->armas.begin(); it!=this->armas.end(); ++it) {
        armas.push_back(it->first);
    }
    return armas;
}

void Registro::set_vida_gusanos(int vida)
{
    this->vida_gusanos = vida;
}

void Registro::set_fondo(QString& nombre)
{
    this->nombre_fondo = nombre;
}

YAML::Emitter& operator << (YAML::Emitter& out, const Registro& obj)
{
    out << YAML::BeginMap;
    out << YAML::Key << "metadata";

       out << YAML::BeginMap;
       out << YAML::Key << "ancho";
       out << YAML::Value << obj.conversor.pixel_a_metros(obj.tam_mapa.first);
       out << YAML::Key << "alto";
       out << YAML::Value << obj.conversor.pixel_a_metros(obj.tam_mapa.second);
       out << YAML::Key << "fondo";
       out << YAML::Value << obj.nombre_fondo.toStdString();
       out << YAML::EndMap;

    out << YAML::Key << "objetos";
    out << YAML::Value << YAML::BeginSeq;

       out << YAML::BeginMap;
       out << YAML::Key << "vida_gusanos";
       out << YAML::Value << obj.vida_gusanos;
       out << YAML::EndMap;

        // Vigas.
        for (unsigned int i = 0; i < obj.vigas.size(); ++i){
            out << *obj.vigas[i];
        }

        // Gusanos.
        for (unsigned int i = 0; i < obj.gusanos.size(); ++i){
            out << *obj.gusanos[i];
        }
        
        out << YAML::EndSeq;

        // Armas.
        out << YAML::Key << "armas";
        out << YAML::Value << YAML::BeginSeq;
        for (map_armas::const_iterator it = obj.armas.begin(); it!=obj.armas.end(); ++it) {
            out << *it->second;
        }

    out << YAML::EndSeq;
    out << YAML::EndMap;
    return out;
}

Registro::~Registro()
{
    for (map_armas::const_iterator it = this->armas.begin(); it!=this->armas.end(); ++it) {
        delete it->second;
    }
}
