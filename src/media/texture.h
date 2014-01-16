#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "../window/window.h"

class Texture {
public:
    Texture(void) {
        _tex  = nullptr;
        _ren  = nullptr;
        _w    = 0;
        _h    = 0;
        _free = false;
    }
    Texture(SDL_Renderer *ren) {
        *this = Texture();
        init(ren);
    }
    ~Texture(void) {
        free();
    }

    void init(SDL_Renderer*);
    void loadIMG(std::string);
    void render(int, int);
    void free(void);

    int getW(void) {return _w;}
    int getH(void) {return _h;}
    SDL_Texture** getTex(void) {return &_tex;}
private:
    SDL_Texture  *_tex;
    SDL_Renderer *_ren;

    int _w, _h;

    bool _free;
};

#endif