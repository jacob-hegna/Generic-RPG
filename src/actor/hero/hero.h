#ifndef _HERO_H_
#define _HERO_H_

#include "../actor.h"

class Hero : public Actor {
public:
	Hero(void) : Actor() {

	}
	~Hero(void) {

	}

	void init(Window *window);
	void move(void);

	bool ifSlash(void) {
		return (_pos==SFRONT||_pos==SBACK||_pos==SLEFT||_pos==SRIGHT);
	}

private:
	SDL_Texture *_multiTex[8];

	enum {
		NFRONT, NBACK, NLEFT, NRIGHT,
		SFRONT, SBACK, SLEFT, SRIGHT
	} _pos;
};

#endif