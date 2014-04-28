#include "actor.h"

void Actor::render(void) {
    if(!_dead) _tex.render(_mapX, _mapY);
}

void Actor::renderRel(void) {
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

bool Actor::isOn(Actor *target) {
    if((target->getX() + target->getW() / 2) > _mapX && (target->getX() + target->getW() / 2) < _mapX + _w) {
        if((target->getY() + target->getH() / 2) > _mapY && (target->getY() + target->getH() / 2) < _mapY + _h) {
            return true;
        }
    }
    return false;
}