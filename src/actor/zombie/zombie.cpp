#include "zombie.h"

void Zombie::init(Window *window) {
    _speed = 1.f;

    _mhealth = 100.f;
    _health  = _mhealth;

    _damage = 3.f;

    _tex.init(window->getRen());
    _tex.loadIMG("media/images/actors/zombie/front.png");
    _w = _tex.getW();
    _h = _tex.getH();

    _hit      = false;
    _hitBuf   = false;
}

void Zombie::hitDetect(Hero *target) {
    if (target->ifAttack()) {
        if ((target->getX() + target->getW() / 2) > _x && (target->getX() + target->getW() / 2) < _x + _w) {
            if ((target->getY() + target->getH() / 2) > _y && (target->getY() + target->getH() / 2) < _y + _h) {
                _hit = true;
            }
            else {
                _hit = false;
            }
        }
        else {
            _hit = false;
        }
    }
    else {
        _hit = false;
    }

    bufFunc(_hit, &_hitBuf,
        [](Hero *hero, Zombie *zombie) {zombie->decHealth(hero->getDamage());},
        target, this);

    if (_health < 0) die();
}

void Zombie::_free(void) {
    _tex.free();
}