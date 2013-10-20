#include "hero.h"

void Hero::init(Window *window) {
	_speed = 0.1f;
	_pos   = NFRONT;

	for(int i = 0; i < 8; ++i) {
		_multiTex[i].init(window->getRen());
	}

	_multiTex[NFRONT].loadIMG("media/images/actors/hero/mainFront.png");
	_multiTex[NBACK].loadIMG("media/images/actors/hero/mainBack.png");
	_multiTex[NLEFT].loadIMG("media/images/actors/hero/mainLeft.png");
	_multiTex[NRIGHT].loadIMG("media/images/actors/hero/mainRight.png");
	_multiTex[SFRONT].loadIMG("media/images/actors/hero/slashFront.png");
	_multiTex[SBACK].loadIMG("media/images/actors/hero/slashBack.png");
	_multiTex[SLEFT].loadIMG("media/images/actors/hero/slashLeft.png");
	_multiTex[SRIGHT].loadIMG("media/images/actors/hero/slashRight.png");

	_w = _multiTex[NFRONT].getW();
	_h = _multiTex[NFRONT].getH();
}

void Hero::move(void) {
	_tex = _multiTex[_pos];
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if(keystate[SDL_GetScancodeFromKey(SDLK_w)]) {
		_y -= _speed;
		_pos = ifSlash() ? SBACK : NBACK;
	}
	if(keystate[SDL_GetScancodeFromKey(SDLK_s)]) {
		_y += _speed;
		_pos = ifSlash() ? SFRONT : NFRONT;
	}
	if(keystate[SDL_GetScancodeFromKey(SDLK_a)]) {
		_x -= _speed;
		_pos = ifSlash() ? SLEFT : NLEFT;
	}
	if(keystate[SDL_GetScancodeFromKey(SDLK_d)]) {
		_x += _speed;
		_pos = ifSlash() ? SRIGHT : NRIGHT;
	}

	if(keystate[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
		switch(_pos) {
			case NFRONT: _pos = SFRONT; break;
			case NBACK:  _pos = SBACK;  break;
			case NLEFT:  _pos = SLEFT;  break;
			case NRIGHT: _pos = SRIGHT; break;
		}
	} else if(!keystate[SDL_GetScancodeFromKey(SDLK_SPACE)]) {
		switch(_pos) {
			case SFRONT: _pos = NFRONT; break;
			case SBACK:  _pos = NBACK;  break;
			case SLEFT:  _pos = NLEFT;  break;
			case SRIGHT: _pos = NRIGHT; break;
		}
	}
}

void Hero::_free(void) {
	for(int i = 0; i < 8; ++i) {
		_multiTex[i].free();
	}
}