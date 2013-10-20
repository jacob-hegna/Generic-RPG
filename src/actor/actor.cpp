#include "actor.h"

void Actor::render(Window *window) {
	window->applyTex(_tex, _x, _y);
}

void Actor::_init(void) {
	_x     = 0;
	_y     = 0;
	_w     = 0;
	_h     = 0;
	_speed = 0;
	_tex   = nullptr;
}