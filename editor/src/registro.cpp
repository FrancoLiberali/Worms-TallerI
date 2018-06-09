#include "registro.h"
#include "gusano.h"
#include "viga.h"
#include <map>
#include <fstream>
#include <iostream>
#include <yaml-cpp/yaml.h>

Registro::Registro() : vida_gusanos(100) {}

void Registro::agregar_viga(Viga* viga)
{
    this->vigas.push_back(viga);
}

void Registro::agregar_arma(std::string& id, Arma* arma)
{
    this->armas[id] = arma;
}

void Registro::agregar_gusano(int equipo, Gusano* gusano)
{
   try{
        this->gusanos.at(equipo).push_back(gusano);
    }
    catch (const std::out_of_range& e) {
        std::vector<Gusano *> gusanos;
        gusanos.push_back(gusano);
        this->gusanos[equipo] = gusanos;
  }
}

void Registro::actualizar_vigas()
{
    vigas.erase(std::remove_if(begin(vigas), end(vigas),
                               [](Viga* x) { return x->esta_eliminado(); }),
                 end(vigas));
}

void Registro::actualizar_gusano(int equipo)
{
    gusanos.at(equipo).erase(std::remove_if(begin(gusanos.at(equipo)), end( gusanos.at(equipo)),
                               [](Gusano* x) { return x->esta_eliminado(); }),
                 end(gusanos.at(equipo)));
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

YAML::Emitter& operator << (YAML::Emitter& out, const Registro& obj)
{
    out << YAML::BeginMap;
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
        for (map_gusanos::const_iterator it = obj.gusanos.begin(); it!=obj.gusanos.end(); ++it) {
            for (unsigned int i = 0; i < it->second.size(); ++i){
                out << *it->second[i];
            }
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
