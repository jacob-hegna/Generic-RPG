#ifndef _HERO_H_
#define _HERO_H_

#include "../actor.h"
#include "../../media/mixer/sound.h"
#include "../../util/buffunc.h"

class Hero : public Actor {
public:
	Hero(void) : Actor() {
		
	}
	Hero(float x, float y) : Actor(x, y) {

	}
	~Hero(void) {
		_free();
	}

	void init(Window *window);
	void move(void);

	bool ifSlash(void) {
		return (_pos==SFRONT||_pos==SBACK||_pos==SLEFT||_pos==SRIGHT);
	}

private:
	void _free(void);

	Texture _multiTex[8];
	Sound   _slashSound;
	bool    _playBuf;

	enum {
		NFRONT, NBACK, NLEFT, NRIGHT,
		SFRONT, SBACK, SLEFT, SRIGHT
	} _pos;
};

#endif