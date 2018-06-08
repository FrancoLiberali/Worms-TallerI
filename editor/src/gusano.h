#ifndef GUSANO_H
#define GUSANO_H
#include "conversor.h"
#include <QPainter>
#include <QGraphicsItem>
#include <yaml-cpp/yaml.h>

enum equipos : int {
    EQUIPO_1 = 1,
    EQUIPO_2,
    EQUIPO_3,
    EQUIPO_4
};

class Gusano : public QGraphicsPixmapItem
{
public:
    // Construye gusano.
    Gusano(int equipo);
    // Setear tipo.
    enum { Type = QGraphicsItem::UserType + 2 };
    int type() const { return Type;}
    void set_eliminado();
    // Decide si esta o no eliminado del mapa.
    // Devuelve verdadero en caso de estarlo, falso en caso contrario.
    bool esta_eliminado();
    // Obtiene el equipo del gusano.
    int get_equipo();
    // Operador << YAML.
    // Escribe gusano sobre out en formato YAML.
    friend YAML::Emitter& operator << (YAML::Emitter& out, const Gusano& obj);
    // Destruye gusano.
    ~Gusano();
private:
    // Equipo al que pertenece.
    int equipo;
    bool eliminado;
    Conversor conversor;
    // Setea la imagen segun el equipo.
    void set_pixmap(int equipo);
};

#endif // GUSANO_H
