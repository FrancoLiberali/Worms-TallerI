#ifndef MANEJADORSONIDO_H
#define MANEJADORSONIDO_H

#include <QMediaPlayer>
#include <QMediaContent>
#include <QMediaResource>
#include <QSoundEffect>

class ManejadorSonido
{
public:
    ManejadorSonido();
    void ejecutarFX(QString);
    void set_volumen(int volume);
    void set_FX_volumen(int volume);
private:
    QSoundEffect *seleccionar, *gusano, *fondo;
    QMediaPlayer *soundPlayer;
};

#endif // MANEJADORSONIDO_H
