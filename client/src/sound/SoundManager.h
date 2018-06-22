#ifndef __SOUND_MANAGER__
#define __SOUND_MANAGER__
#include <SDL2/SDL_mixer.h>
#include <map>
#include <string>
#include <SDL2/SDL.h>

enum SoundId {AIRSTRIKE,BANANA_S,EXPLOTION, FUSE, HOLY_S, SHOOT, JUMP_S, COMMUNICATOR,
    TELELEPORT_S, BAT_IMPACT, BAT_JINGLE, BYE};

enum MusicId {BACKGROUND, WAIT,};

class SoundManager
{
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
    void loadSound(SoundId id, std::string path);
    void loadMusic(MusicId id, std::string path);
    void playSound(SoundId id, int times = 0, int channel = -1);
    void playMusic(MusicId id);
};

#endif