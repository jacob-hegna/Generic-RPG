#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <SDL_image.h>

#include "../window/window.h"
#include "../media/texture.h"

class Actor {
public:
    Actor(void) {
        _init();
    }
    Actor(float x, float y) {
        _init(x, y);
    }
    ~Actor(void) {
        
    }

    void setWin(Window *window) {
        _tex.init(window->getRen());
    }

    void render(void);
    void die(void);

    float getX(void)      {return _x;}
    float getY(void)      {return _y;}
    float getW(void)      {return _w;}
    float getH(void)      {return _h;}
    float getHealth(void) {return _health;}
    float getDamage(void) {return _damage;}
    float getDead(void)   {return _dead;}
protected:
    float _x, _y;
    float _w, _h;
    float _speed;
    float _health,
          _mhealth;
    float _damage;
    bool  _dead;
            

    Texture _tex;

    void _init(float x = 0, float y = 0);
};

#endif