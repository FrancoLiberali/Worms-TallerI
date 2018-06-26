#ifndef GUSANO_H
#define GUSANO_H
#include "conversor.h"
#include <QPainter>
#include <QGraphicsItem>
#include <yaml-cpp/yaml.h>

class Gusano : public QGraphicsPixmapItem
{
public:
    // Construye gusano.
    Gusano();
    // Setear tipo.
    enum { Type = QGraphicsItem::UserType + 2 };
    int type() const { return Type;}
    void set_eliminado();
    // Decide si esta o no eliminado del mapa.
    // Devuelve verdadero en caso de estarlo, falso en caso contrario.
    bool esta_eliminado();
    // Operador << YAML.
    // Escribe gusano sobre out en formato YAML.
    friend YAML::Emitter& operator << (YAML::Emitter& out, const Gusano& obj);
    // Setea la posicion de un gusano.
    void set_pos(QPointF pos);
    // Destruye gusano.
    ~Gusano();
private:
    bool eliminado;
    Conversor conversor;
};

#endif // GUSANO_H
