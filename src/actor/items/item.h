#ifndef __ITEM_H_
#define __ITEM_H_

#include <string>

#include "../../engine/engine.h"
#include "../actor.h"

class Item : public Actor {
public:
    Item(void) {

    }
    Item(float x, float y) : Actor(x, y) {
        Item();
    }
    ~Item(void) {

    }

    void use(void(*_use)(Engine *engine), Engine *engine) {
        // will be abstraced in branch classes
        // can't be virtual because it is called in logic(Actor *target, voic(*_use)(void))
    }

    void logic(Actor *target, void(*_use)(Engine *engine), Engine *engine, float offX, float offY) {
        _mapX = _x - offX;
        _mapY = _y - offY;
        const Uint8* keystate = SDL_GetKeyboardState(NULL);
        if(keystate[SDL_GetScancodeFromKey(SDLK_e)]) {
            if(this->isOn(target)) {
                this->use(_use, engine);
            }
        }
    }
protected:
    void _init(Window *window, std::string path) {
        _tex.init(window->getRen());
        _tex.loadIMG(path);
        _w = _tex.getW();
        _h = _tex.getH();
    }
};

#endif