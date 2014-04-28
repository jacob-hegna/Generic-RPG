#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <png++/png.hpp>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "../../globals.h"
#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"
#include "../../actor/enemy/zombie.h"
#include "../../actor/enemy/skeleton.h"
#include "../../actor/items/portal.h"
#include "../../media/font.h"
#include "../../media/mixer/music.h"
#include "../../media/texture.h"
#include "map.h"

namespace Gameplay {
    extern Map map;

    extern Hero *hero;
    extern std::vector<Zombie*> zombie;
    extern std::vector<Skeleton*> skeleton;
    extern Portal portal;

    namespace LevelData {
        // char uses less data than int
        extern       char currentLevel;
        extern       bool levelClear;
        static const char levelAmt       = 2; // zero delimited
        static const char zombieAmt[3]   = {3,5,7};
        static const char skeletonAmt[3] = {5,7,8};
    };

    extern Font arial;
    extern Music music;

    struct HUD {
        Texture bar;
        Texture healthTick;
        Texture magicTick;
    };
    extern HUD hud;

    void init(Engine *engine);
    void logic(Engine *engine);
    void render(Engine *engine);
    void renderHUD(Engine *engine);
    void free(Engine *engine);

    void nextLevel(Engine *engine);
};

#endif