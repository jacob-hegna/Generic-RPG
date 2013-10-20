#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <SDL_image.h>

#include "../window/window.h"

class Actor {
public:
	Actor(void) {

	}
	~Actor(void) {

	}

	void render(Window* window);
protected:
	float _x, _y;
	float _w, _h;
	float _speed;

	SDL_Texture *_tex;

	void _init(void);
};

#endif