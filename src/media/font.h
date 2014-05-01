#ifndef _FONT_H_
#define _FONT_H_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../window/window.h"

class Font {
public:
    Font(void) {
        _font = nullptr;
        _tex  = nullptr;
    }
    Font(Window *window, std::string path, int size) {
        *this = Font();
        _ren  = window->getRen();
        loadTTF(path, size);
    }

    void loadTTF(std::string, int);
    void setRen(Window *window) {_ren = window->getRen();}
    void setColor(Uint8 r, Uint8 g, Uint8 b);
    void print(std::string, int x, int y);
    void free(void);

    int getSize(void) {
        return _size;
    }
    int getW(void) {
        return _w;
    }
    int getH(void) {
        return _h;
    }
private:
    TTF_Font     *_font;
    SDL_Texture  *_tex;
    SDL_Renderer *_ren;
    SDL_Color     _color;

    int _size;
    int _w, _h;
};

#endif