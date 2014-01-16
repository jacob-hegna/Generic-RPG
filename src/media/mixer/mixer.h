#ifndef _MIXER_H_
#define _MIXER_H_

#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

class Mixer {
public:
    Mixer(void) {

    }
    Mixer(std::string path) {
        init(path);
    }
    ~Mixer(void) {

    }

    virtual void init(std::string path) = 0;
    virtual void play(void)             = 0;
    virtual void free(void)             = 0;
protected:
};

#endif