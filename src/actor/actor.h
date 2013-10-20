#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <SDL_image.h>

#include "../window/window.h"

class Actor {
public:
	Actor(void) {
		_init();
	}
	Actor(float x, float y) {
		_init(x, y);
	}
	~Actor(void) {
		SDL_DestroyTexture(_tex);
		delete _tex;
	}

	void render(Window* window);

	float getX(void) {return _x;}
	float getY(void) {return _y;}
	float getW(void) {return _w;}
	float getH(void) {return _h;}
protected:
	float _x, _y;
	float _w, _h;
	float _speed;

	SDL_Texture *_tex;

	void _init(float x = 0, float y = 0);
};

#endif