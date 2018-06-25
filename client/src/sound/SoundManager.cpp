#include "SoundManager.h"
#include "../exception/GameException.h"
#include <string>

void SoundManager::init(){
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2 ,2048) < 0)
        throw GameException("Error al cargar el MIXER");
    Mix_AllocateChannels(100);
}

void SoundManager::loadSound(SoundId id, std::string path){
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (!sound){
        std::string msg = "No se encontro el archivo ";
        msg += path;
        throw GameException(msg.c_str());
    }
    this->sounds.emplace(id, sound);
}

void SoundManager::loadMusic(MusicId id, std::string path){
    Mix_Music* music = Mix_LoadMUS(path.c_str());
    if (!music){
        std::string msg = "No se encontro el archivo ";
        msg += path;
        throw GameException(msg.c_str());
    }
    this->musics.emplace(id, music);
}

void SoundManager::close(){
    for (auto& it: sounds)
        Mix_FreeChunk(it.second);
    
    for (auto& it: musics)
        Mix_FreeMusic(it.second);
	Mix_Quit();
}

void SoundManager::playSound(SoundId id, int times, int channel){
    if (Mix_PlayChannel(channel, sounds[id], times) < 0){
        throw GameException("Error al reproducir el sonido");
    }
}

void SoundManager::stopAllSounds(){
    Mix_HaltChannel(-1);
}

void SoundManager::playMusic(MusicId id){
    if(Mix_PlayingMusic() == 0){
		if (Mix_PlayMusic(musics[id], -1) < 0)
            throw GameException("Error al reproducir la musica");
	}else if (Mix_PausedMusic() == 1){
		Mix_ResumeMusic();
	} 
    else{
		Mix_PauseMusic();
	}
}