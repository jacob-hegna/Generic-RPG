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
    _soundBuf = false;
    _hitSound.init("media/audio/zombHit.wav");
}

void Zombie::move(Hero *hero) {
    if(hero->getX() > _x) _x += _speed;
    if(hero->getX() < _x) _x -= _speed;
    if(hero->getY() > _y) _y += _speed;
    if(hero->getY() < _y) _y -= _speed;

    if(hero->ifSlash()) {
        if((hero->getX()+hero->getW()/2) > _x && (hero->getX()+hero->getW()/2) < _x+_w) {
            if((hero->getY()+hero->getH()/2) > _y && (hero->getY()+hero->getH()/2) < _y+_h) {
                _hit = true;
            } else {
                _hit = false;
            }
        } else {
            _hit = false;
        }
    } else {
        _hit = false;
    }
    bufFunc(_hit, &_soundBuf,
            [] (Hero *hero, Zombie *zombie) {zombie->getSound()->play();zombie->decHealth(hero->getDamage());},
            hero, this);

    if(_health < 0) die();
}

void Zombie::_free(void) {
    _hitSound.free();
    _tex.free();
}