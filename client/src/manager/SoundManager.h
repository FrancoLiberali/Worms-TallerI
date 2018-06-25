#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <SDL2/SDL.h>

#include "sound.h"

/*
*@class SoundManager
* Usa el patrón singletón, se encarga del manejo de los sonidos
* es decir reproducirlo todos los sonidos son almacenados en un 
* diccionario de sonidos.
*/
class SoundManager{
private:
    std::map<SoundId,Mix_Chunk*> sounds;
    std::map<MusicId, Mix_Music*> musics;
public:
	static SoundManager & Instance(){
			static SoundManager theSoundManager;
			return theSoundManager;
	}
	void init();
	void close();
    //carga un sonido
    //Pre:Id de un sonido válido y la ruta del archivo
    //si ocurre un error lanza GameException
    void loadSound(SoundId id, std::string path);
     //carga una musica
    //Pre:Id de un sonido válido y la ruta del archivo
    //si ocurre un error lanza GameException
    void loadMusic(MusicId id, std::string path);
     //Reproduce un sonido
    //Pre:Id de un sonido válido, el numero de repeticiones y el canal.
    //si ocurre un error lanza GameException
    void playSound(SoundId id, int times = 0, int channel = -1);
     //Reproduce una musica
    //Pre:Id de la música es válida.
    //si ocurre un error lanza GameException
    void playMusic(MusicId id);
    //Detiene todos los sonidos(en todo los canales).
    void stopAllSounds();
};

#endif