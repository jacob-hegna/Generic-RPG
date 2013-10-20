#include "zombie.h"

void Zombie::init(Window *window) {
	_speed = 1.f;
	_tex.init(window->getRen());
	_tex.loadIMG("media/images/actors/zombie/front.png");
	_w = _tex.getW();
	_h = _tex.getH();
}

void Zombie::move(Hero *hero) {
	if(hero->getX() > _x) _x += _speed;
	if(hero->getX() < _x) _x -= _speed;
	if(hero->getY() > _y) _y += _speed;
	if(hero->getY() < _y) _y -= _speed;
}

void Zombie::_free(void) {
	_tex.free();
}