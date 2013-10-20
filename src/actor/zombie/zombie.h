#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include <cmath>

#include "../actor.h"
#include "../hero/hero.h"
#include "../../window/window.h"

class Zombie : public Actor {
public:
	Zombie(void) : Actor() {

	}
	Zombie(float x, float y) : Actor(x, y) {

	}
	~Zombie(void) {
		_free();
	}

	void init(Window *window);
	void move(Hero *hero);

private:
	void _free();
};

#endif