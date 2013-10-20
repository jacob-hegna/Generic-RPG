#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "../../engine/engine.h"
#include "../../actor/hero/hero.h"

namespace Gameplay {
	extern Hero *hero;

	void init(Engine *engine);
	void logic(Engine *engine);
	void render(Engine *engine);
};

#endif