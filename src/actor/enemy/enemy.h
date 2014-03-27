#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../hero/hero.h"
#include "../../map/map.h"

class Enemy : public Actor {
public:
    Enemy(void);
    Enemy(float x, float y) : Actor(x, y) {
        Enemy();
    }

    ~Enemy(void) {
        _free();
    }

    void move(Actor *actor, Gameplay::Map *map);
    void hitDetect(Hero *target);

protected:
    bool _hitBuf;

    void _init(Window *window, float speed, float health, float damage, std::string path);
    void _free(void);
};

#endif