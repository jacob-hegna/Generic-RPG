#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <vector>

#include <SDL.h>
#include <SDL_ttf.h>

#include <png++/png.hpp>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"
#include "../../actor/zombie/zombie.h"
#include "../../media/font.h"
#include "../../media/mixer/music.h"
#include "../../util/sstr.h"

namespace Gameplay {
    struct Tile {
        Tile(void) {}
        Tile(std::string name) {this->name = name;}
        std::string name, path;
        Texture tex;
        Uint8 r, g, b;
    };
    
    extern std::vector<Tile> tiles;
    extern int **mapTiles;
    extern int mapW, mapH;
    extern Hero *hero;
    extern Zombie *zombie;
    extern Font arial;
    extern Music music;

    void init(Engine *engine);
    void logic(Engine *engine);
    void render(Engine *engine);
    void free(Engine *engine);
};

#endif