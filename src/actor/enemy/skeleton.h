#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "enemy.h"
#include "../../util/randf.h"

class Skeleton : public Enemy {
public:
    Skeleton(void) : Enemy() {}
    Skeleton(float x, float y) : Enemy(x, y) {}
    void init(Window *window) {
        _init(window,
            randF(1.3f, 1.7f),
            60.f,
            2.25f,
            "media/images/actors/skel/front.png");
    }
};

#endif