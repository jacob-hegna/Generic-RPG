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

void Actor::autoMove(Actor *target) {
    /* Only allows movement in diagonals and up/down/left/right
    if(hero->getX() > _x) _x += _speed;
    if(hero->getX() < _x) _x -= _speed;
    if(hero->getY() > _y) _y += _speed;
    if(hero->getY() < _y) _y -= _speed;
    */

    float r = sqrt(pow(this->getXMid() - target->getXMid(), 2) + pow(this->getYMid() - target->getYMid(), 2));
    float theta = asin((this->getYMid() - target->getYMid()) / r);

    _x += _speed * (this->getXMid() <= target->getXMid()) ? cos(theta) : -cos(theta);
    _y -= _speed * sin(theta);

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
