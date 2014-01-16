#ifndef _SOUND_H_
#define _SOUND_H_

#include "mixer.h"

class Sound : public Mixer {
public:
    Sound(void) : Mixer() {
        _sound = nullptr;
    }
    Sound(std::string path) : Mixer(path) {
        *this = Sound();
    }
    ~Sound(void) {

    }

    void init(std::string path) {_sound = Mix_LoadWAV(path.c_str());}
    void play(void) {Mix_PlayChannel(-1, _sound, 0);}
    void free(void) {if(_sound!=nullptr){Mix_FreeChunk(_sound);delete _sound;}}

private:
    Mix_Chunk *_sound;
};

#endif