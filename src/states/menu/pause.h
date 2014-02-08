#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "../../engine/engine.h"

namespace PauseMenu {
    void init(Engine *engine);
    void logic(Engine *engine);
    void render(Engine *engine);
    void free(Engine *engine);
};

#endif