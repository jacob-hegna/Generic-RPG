#include "actor.h"

void Actor::render(void) {
	_tex.render(_x, _y);
}

void Actor::_init(float x, float y) {
	_x     = x;
	_y     = y;
	_w     = 0;
	_h     = 0;
	_speed = 0;
	_tex   = Texture();
}