#ifndef _LOOP_H_
#define _LOOP_H_

#include "../window/window.h"

#include "gameplay/gameplay.h"
#include "menu/pause.h"

enum Gamestates {
    GAMEPLAY,
    PAUSEMENU
};
extern Gamestates gamestates;
static const int stateAmt = 2;

int loop(Window *window);

#endif