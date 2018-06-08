#include "manejadorsonido.h"

ManejadorSonido::ManejadorSonido()
{
    this->seleccionar = new QSoundEffect;
    seleccionar->setSource(QUrl("file:/home/bauticanavese/Demo/sonido/CursorSelect.wav"));
    seleccionar->setLoopCount(0);
    seleccionar->setVolume(.25f);

    this->gusano = new QSoundEffect;
    gusano->setSource(QUrl("file:/home/bauticanavese/Demo/sonido/HELLO.WAV"));
    gusano->setLoopCount(0);
    gusano->setVolume(.25f);

    this->soundPlayer = new QMediaPlayer;
    soundPlayer->setMedia(QUrl("file:/home/bauticanavese/Demo/sonido/editor.mp3"));
    soundPlayer->play();
}


void ManejadorSonido::ejecutarFX(QString which){

    if(which == "seleccionar"){
        seleccionar->play();
    } else if (which == "gusano") {
        gusano->play();
    }
}

void ManejadorSonido::set_volumen(int volume){
    this->soundPlayer->setVolume(volume);
}
void ManejadorSonido::set_FX_volumen(int volume){
    qreal qVolume = volume;
    qVolume /=100;

    //this->inicio->setVolume(qVolume);
}
