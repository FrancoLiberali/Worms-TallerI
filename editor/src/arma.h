#ifndef ARMA_H
#define ARMA_H
#include <QString>
#include <yaml-cpp/yaml.h>

class Arma
{
private:
    std::string tipo;
    std::string habilitada;
    std::string municion;
public:
    // Construye arma.
    Arma();
    // Setea el tipo de arma (nombre)
    void set_tipo(std::string tipo);
    // Setea que esta habilitada para usar.
    void set_habilitada();
    // Setea que no esta habilitada para usar.
    void set_deshabilitada();
    // Setea la municion.
    // Puede ser tanto un numero como "Infinitas".
    void set_municion(std::string municion);
    // Obtiene el tipo.
    std::string get_tipo() const;
    // Obtiene la municion.
    std::string get_municion() const;
    // Decide si esta habilitada o no.
    // Devuelve verdadero en caso de estarlo, falso en caso
    // contrario.
    bool esta_habilitada() const;
    // Operador << YAML
    friend YAML::Emitter& operator << (YAML::Emitter& out, const Arma& arma);
};

#endif // ARMA_H
