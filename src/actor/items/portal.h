#ifndef __PORTAL_H_
#define __PORTAL_H_

#include "item.h"

class Portal : public Item {
public:
    Portal(void) : Item() {}
    Portal(float x, float y) : Item(x, y) {Item();}

    void init(Window *window, std::string path) {
        _init(window, path);
    }

    void use(void(*_use)(Engine *engine), Engine *engine) {
        if(_use != nullptr) _use(engine);
    }
};

#endif