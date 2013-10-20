#ifndef _LOOP_H_
#define _LOOP_H_

#include "../window/window.h"

#include "gameplay/gameplay.h"

enum Gamestates {
	GAMEPLAY
};
extern Gamestates gamestates;
static const int stateAmt = 1;

int loop(Window *window);

#endif