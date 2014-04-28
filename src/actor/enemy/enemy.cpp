#include "enemy.h"

Enemy::Enemy(void) {
    _hit      = false;
    _hitBuf   = false;
}

void Enemy::_init(Window *window, float speed, float health, float damage, std::string path) {
    _speed = speed;
    _mhealth = health;
    _health  = _mhealth;

    _damage = damage;

    _tex.init(window->getRen());
    _tex.loadIMG(path);
    _w = _tex.getW();
    _h = _tex.getH();
}

void Enemy::move(Actor *target, Gameplay::Map *map) {
    float r = sqrt(pow(_mapX+_w/2 - target->getXMid(), 2) + pow(_mapY+_h/2 - target->getYMid(), 2));
    float theta = asin((_mapY+_h/2 - target->getYMid()) / r);

    _x += (_mapX+_w/2 <= target->getXMid()) ? _speed * cos(theta) : _speed * -cos(theta);
    _y -= _speed * sin(theta);

    _mapX = _x - map->x;
    _mapY = _y - map->y;
}

void Enemy::hitDetect(Hero *target) {
    _hit = false;
    if(this->isOn(target)) {
        target->hurt(_damage);
        if (target->ifAttack()) {
            _hit = true;
        }
    }

    if(target->isMagicAttack()) {
        if(_mapX < target->getX() + 250 && _mapX > target->getX() - 250) {
            if (_mapY < target->getY() + 250 && _mapY > target->getY() - 250) {
                _health -= 6;
            }
        }
    }

    bufFunc(_hit, &_hitBuf,
        [](Hero *hero, Enemy *enemy) {enemy->hurt(hero->getDamage());},
        target, this);

    if (_health < 0) die();
}

void Enemy::respawn(float x, float y) {
    _dead = false;
    _health = _mhealth;
    _x = x;
    _y = y;
}

void Enemy::_free(void) {
    _tex.free();
}