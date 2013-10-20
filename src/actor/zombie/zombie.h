#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include <cmath>

#include "../actor.h"
#include "../hero/hero.h"
#include "../../window/window.h"
#include "../../media/mixer/sound.h"
#include "../../util/buffunc.h"

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

	void decHealth(float amt) {_health -= amt;}
	Sound* getSound(void) {return &_hitSound;}
private:
	void _free();

	bool _hit;
	bool _soundBuf;
	Sound _hitSound;
};

#endif