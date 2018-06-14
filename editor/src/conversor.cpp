#include "conversor.h"

#define ESCALA (140/6)

Conversor::Conversor() {}

QPair<float,float> Conversor::a_metros(const QGraphicsPixmapItem &obj, float angulo) const
{
    float x_centro, y_centro;
    float alto = obj.pixmap().height();
    float ancho = obj.pixmap().width();
    angulo = a_radianes(angulo);
    float radio = ancho/2;
    x_centro = obj.pos().x() + alto/2 * qSin(angulo) + radio * qCos(angulo);
    y_centro = obj.pos().y() + alto/2 * qCos(angulo) - radio * qSin(angulo);
    x_centro = pixel_a_metros(x_centro);
    y_centro = pixel_a_metros(y_centro);
    return QPair<float,float>(x_centro, y_centro);
}

float Conversor::a_radianes(float angulo) const
{
    return qDegreesToRadians(angulo);
}

float Conversor::pixel_a_metros(float pixel) const 
{
    return pixel / ESCALA;
}

// QPointF Conversor::a_pixeles(const QPair<float,float> pos) const
// {
//     float x, y;
//     float radio = ancho/2;
//     x = pos.first - alto/2 * qSin(angulo) - radio * qCos(angulo);
//     y = pos.second - alto/2 * qCos(angulo) + radio * qSin(angulo);
//     x *= ESCALA;
//     y *=  ESCALA;
//     return QPointF(x, y);
// }
