#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"
#include "../../actor/zombie/zombie.h"

namespace Gameplay {
	extern Hero *hero;
	extern Zombie *zombie[];

	void init(Engine *engine);
	void logic(Engine *engine);
	void render(Engine *engine);
};

#endif