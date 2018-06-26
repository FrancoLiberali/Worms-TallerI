#ifndef VIGA_H
#define VIGA_H
#include "conversor.h"
#include <QGraphicsItem>
#include <yaml-cpp/yaml.h>

class Viga : public QGraphicsPixmapItem
{
public:
    // Crea una viga.
    Viga(int angulo);
    // Sete la posicion de una viga.
    void set_pos(QPointF pos);
    // Setea eliminado.
    void set_eliminado();
    // Decide si la viga fue eliminada, en caso de serlo
    // devuelve verdadero, falso en caso contrario.
    bool esta_eliminado();
    // Enum.
    enum { Type = QGraphicsItem::UserType + 1 };
    int type() const { return Type;}
    // Escribe obj sobre un emitidor de yaml.
    friend YAML::Emitter& operator<<(YAML::Emitter& out, const Viga& obj);
protected:
    int angulo;
    bool eliminado;
    // Escribe sobre el emitidor yaml.
    virtual void escribir(YAML::Emitter& out) const = 0;
    Conversor conversor;
};

#endif // VIGA_H
