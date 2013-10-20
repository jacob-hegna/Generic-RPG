#include "zombie.h"

void Zombie::init(Window *window) {
	_speed = 0.06f;
	_tex = window->loadTex("media/images/actors/zombie/front.png");
}

void Zombie::move(Hero *hero) {
	if(hero->getX() > _x) _x += _speed;
	if(hero->getX() < _x) _x -= _speed;
	if(hero->getY() > _y) _y += _speed;
	if(hero->getY() < _y) _y -= _speed;
}