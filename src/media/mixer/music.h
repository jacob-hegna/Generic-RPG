#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "mixer.h"

class Music : public Mixer {
public:
    Music(void) : Mixer() {
        _music = nullptr;
    }
    Music(std::string path) : Mixer(path) {
        *this = Music();
    }
    ~Music(void) {
        
    }

    void init(std::string path) {_music = Mix_LoadMUS(path.c_str());}
    void play(void) {Mix_PlayMusic(_music, -1);}
    void free(void) {if(_music!=nullptr){Mix_FreeMusic(_music);delete _music;}}

private:
    Mix_Music *_music;
};

#endif