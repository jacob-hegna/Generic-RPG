#include "hero.h"

void Hero::init(Window *window) {
    _speed = 2.f;

    _mhealth = 500.f;
    _health  = _mhealth;
    _mMagic  = 100.f;
    _magic   = _mMagic;
    _damage  = 5.f;

    _pos   = NFRONT;

    for(int i = 0; i < 8; ++i) {
        _multiTex[i].init(window->getRen());
    }
    _magicTex.init(window->getRen());

    _multiTex[NFRONT].loadIMG("media/images/actors/hero/mainFront.png");
    _multiTex[NBACK].loadIMG("media/images/actors/hero/mainBack.png");
    _multiTex[NLEFT].loadIMG("media/images/actors/hero/mainLeft.png");
    _multiTex[NRIGHT].loadIMG("media/images/actors/hero/mainRight.png");
    _multiTex[SFRONT].loadIMG("media/images/actors/hero/slashFront.png");
    _multiTex[SBACK].loadIMG("media/images/actors/hero/slashBack.png");
    _multiTex[SLEFT].loadIMG("media/images/actors/hero/slashLeft.png");
    _multiTex[SRIGHT].loadIMG("media/images/actors/hero/slashRight.png");

    _magicTex.loadIMG("media/images/actors/hero/magicAttack.png");

    _w = _multiTex[NFRONT].getW();
    _h = _multiTex[NFRONT].getH();

    _slashSound.init("media/audio/slash.wav");
    _playBuf = false;
}

void Hero::move(Gameplay::Map *map) {
    _tex = _multiTex[_pos];
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if(keystate[SDL_GetScancodeFromKey(SDLK_w)]) {
        (_y > map->bufT) ? _y -= _speed : map->y -= _speed;
        _pos = ifAttack() ? SBACK : NBACK;
    }
    if(keystate[SDL_GetScancodeFromKey(SDLK_s)]) {
        (_y + _h < map->bufD) ? _y += _speed : map->y += _speed;
        _pos = ifAttack() ? SFRONT : NFRONT;
    }
    if(keystate[SDL_GetScancodeFromKey(SDLK_a)]) {
        (_x > map->bufL) ? _x -= _speed : map->x -= _speed;
        _pos = ifAttack() ? SLEFT : NLEFT;
    }
    if(keystate[SDL_GetScancodeFromKey(SDLK_d)]) {
        (_x + _w < map->bufR) ? _x += _speed : map->x += _speed;
        _pos = ifAttack() ? SRIGHT : NRIGHT;
    }

    // magic healing
    if(keystate[SDL_GetScancodeFromKey(SDLK_q)]) {
        if(_magic > 0 && _health <= _mhealth - 4.f) {
            _magic -= 0.7f;
            _health += 4.f;
        }
    }

    // magic attack
    if(keystate[SDL_GetScancodeFromKey(SDLK_z)] && _magic >= 5) {
        _magicAttack = true;
        _magic -= 5;
    } else {
        _magicAttack = false;
    }

    bufFunc(keystate[SDL_GetScancodeFromKey(SDLK_SPACE)], &_playBuf,
            [] (Sound *sound, void *p) {sound->play();},
            &_slashSound, nullptr);

    if(keystate[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
        switch(_pos) {
            case NFRONT: _pos = SFRONT; break;
            case NBACK:  _pos = SBACK;  break;
            case NLEFT:  _pos = SLEFT;  _x -= 26; break;
            case NRIGHT: _pos = SRIGHT; break;
        }
    } else if(!keystate[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
        switch(_pos) {
            case SFRONT: _pos = NFRONT; break;
            case SBACK:  _pos = NBACK;  break;
            case SLEFT:  _pos = NLEFT;  _x += 26; break;
            case SRIGHT: _pos = NRIGHT; break;
        }
    }

    _mapX = _x + map->x;
    _mapY = _y + map->y;

    // regen magic
    if(_magic <= _mMagic - .25) {
        _magic += .25f;
    }
}

void Hero::renderMagic(void) {
    if(_magicAttack) {
        _magicTex.render(_x - _magicTex.getW() / 2 + _w/2, _y - _magicTex.getH() / 2 + _h/2);
    }
}

void Hero::_free(void) {
    _slashSound.free();
    for(int i = 0; i < 8; ++i) {
        _multiTex[i].free();
    }
}