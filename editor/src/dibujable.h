#ifndef DIBUJABLE_H
#define DIBUJABLE_H
#include <yaml-cpp/yaml.h>
#include <QGraphicsItem>

class Dibujable : public QGraphicsPixmapItem
{
public:
    Dibujable();
    virtual friend YAML::Emitter& operator<<(YAML::Emitter& out, const Dibujable& obj);
};

#endif // DIBUJABLE_H
