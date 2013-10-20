#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"
#include "../../actor/zombie/zombie.h"
#include "../../util/font.h"
#include "../../util/sstr.h"

namespace Gameplay {
	extern Hero *hero;
	extern Zombie *zombie;
	extern Font arial;

	void init(Engine *engine);
	void logic(Engine *engine);
	void render(Engine *engine);
	void free(Engine *engine);
};

#endif