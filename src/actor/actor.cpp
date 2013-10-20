#include "actor.h"

void Actor::render(void) {
	if(!_dead) _tex.render(_x, _y);
}

void Actor::die(void) {
	_dead = true;
	_x    = 0;
	_y    = 0;
	_w    = 0;
	_h    = 0;
}

void Actor::_init(float x, float y) {
	_x        = x;
	_y        = y;
	_w        = 0;
	_h        = 0;
	_speed    = 0;
	_health   = 0;
	_mhealth  = 0;
	_damage   = 0;
	_dead     = false;
	_tex      = Texture();
}