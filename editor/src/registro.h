#ifndef REGISTRO_H
#define REGISTRO_H
#include <QPair>
#include "gusano.h"
#include "vigagrande.h"
#include "arma.h"
#include "conversor.h"

typedef typename std::map<std::string, Arma*> map_armas;

class Registro
{
private:
    map_armas armas;
    std::vector<Gusano*> gusanos;
    std::vector<Viga*> vigas;
    int vida_gusanos;
    QPair<float,float> tam_mapa;
    Conversor conversor;
public:
    // Construye Registro.
    Registro();
    // Agrega una viga.
    void agregar_viga(Viga* viga);
    // Agrega un gusano.
    // En el caso de que el id no se encuentre en el registro,
    // lo crea.
    void agregar_gusano(Gusano* gusano);
    // Agrega un arma.
    void agregar_arma(std::string& id, Arma* arma);
    // Actualiza las vigas del registro.
    void actualizar_vigas();
    // Actualiza los gusanos del equipo indicado.
    void actualizar_gusano();
    // Obtiene la cantidad de gusanos en el mapa.
    unsigned int get_cant_gusanos() const;
    // Obtiene la caontidad de vigas en el mapa.
    unsigned int get_cant_vigas() const;
    // Setea la vida de los gusanos.
    void set_vida_gusanos(int vida);
    // Obtiene un arma.
    Arma* get_arma(const std::string& nombre) const;
    // Obtiene una lista con los nombres de las aramas.
    // En un orden indefinido.
    std::vector<std::string> get_armas() const;
    // Setea el tamanio de mapa (en pixeles).
    void set_tam_mapa(float ancho, float alto);
    // Escribe obj sobre out en formato YAML.
    friend YAML::Emitter& operator << (YAML::Emitter& out, const Registro& obj);
    // Destruye Registro.
    ~Registro();
};

#endif // REGISTRO_H
