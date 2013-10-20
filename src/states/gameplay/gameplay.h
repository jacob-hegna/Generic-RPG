#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

#include "../../engine/engine.h"

namespace Gameplay {
	void init(Engine *engine);
	void logic(Engine *engine);
	void render(Engine *engine);
};

#endif