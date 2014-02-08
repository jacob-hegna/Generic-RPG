#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include "enemy.h"
#include "../../util/randf.h"

class Zombie : public Enemy {
public:
    Zombie(void) : Enemy() {}
    Zombie(float x, float y) : Enemy(x, y) {}
    void init(Window *window) {
        _init(window,
            randF(.8f, 1.2f),
            100.f,
            3.f,
            "media/images/actors/zombie/front.png");
    }
};

#endif