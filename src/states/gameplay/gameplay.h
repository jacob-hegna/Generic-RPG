#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include <SDL.h>
#include <SDL_ttf.h>

#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"
#include "../../actor/zombie/zombie.h"
#include "../../media/font.h"
#include "../../media/mixer/music.h"
#include "../../util/sstr.h"

namespace Gameplay {
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