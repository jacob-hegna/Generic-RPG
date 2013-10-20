#include "hero.h"

void Hero::init(Window *window) {
	_w     = 100;
	_h     = 126;
	_speed = 0.1f;
	_pos   = NFRONT;

	_multiTex[NFRONT] = window->loadTex("media/images/actors/hero/mainFront.png");
	_multiTex[NBACK]  = window->loadTex("media/images/actors/hero/mainBack.png");
	_multiTex[NLEFT]  = window->loadTex("media/images/actors/hero/mainLeft.png");
	_multiTex[NRIGHT] = window->loadTex("media/images/actors/hero/mainRight.png");
	_multiTex[SFRONT] = window->loadTex("media/images/actors/hero/slashFront.png");
	_multiTex[SBACK]  = window->loadTex("media/images/actors/hero/slashBack.png");
	_multiTex[SLEFT]  = window->loadTex("media/images/actors/hero/slashLeft.png");
	_multiTex[SRIGHT] = window->loadTex("media/images/actors/hero/slashRight.png");
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