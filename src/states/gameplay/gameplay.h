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
#include "../../actor/enemy/zombie.h"
#include "../../actor/enemy/skeleton.h"
#include "../../media/font.h"
#include "../../media/mixer/music.h"
#include "../../util/sstr.h"
#include "map.h"

namespace Gameplay {
    extern Map map;

    extern Hero *hero;
    extern std::vector<Zombie*> zombie;
    extern std::vector<Skeleton*> skeleton;
    static const int zombieAmt   = 3;
    static const int skeletonAmt = 3;

    extern Font arial;
    extern Music music;

    void init(Engine *engine);
    void logic(Engine *engine);
    void render(Engine *engine);
    void free(Engine *engine);
};

#endif