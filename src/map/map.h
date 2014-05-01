#ifndef _MAP_H_
#define _MAP_H_

#include <string>

#include <SDL2/SDL.h>

#include "../media/texture.h"

class Map {
public:
    Map(void) {

    }
    Map(std::string path) {
        init(path);
    }
    ~Map(void) {

    }

    void init(std::string path);
    void render(void);
    void free(void);

private:
    Texture **_tex;

    int _w, _h;
};

#endif