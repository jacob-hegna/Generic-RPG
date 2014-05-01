#ifndef _ACTOR_H_
#define _ACTOR_H_

#include <SDL2/SDL_image.h>

#include "../window/window.h"
#include "../media/texture.h"
#include "../states/gameplay/map.h"

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
    void renderRel(void);
    void render(float x, float y); // for use in the Item classes
    void die(void);
    void autoMove(Actor *actor, Gameplay::Map *map);

    bool isOn(Actor *target);

    void hurt(float amt) {_health -= amt;}

    float getX(void)       {return _x;}
    float getY(void)       {return _y;}
    float getMapX(void)    {return _mapX;}
    float getMapY(void)    {return _mapY;}
    float getW(void)       {return _w;}
    float getH(void)       {return _h;}
    float getXMid(void)    {return _x+_w/2;}
    float getYMid(void)    {return _y+_h/2;}
    float getHealth(void)  { return _health; }
    float getMHealth(void) { return _mhealth; }
    float getDamage(void)  {return _damage;}
    float getDead(void)    {return _dead;}
protected:
    float _x, _y;
    float _mapX, _mapY;
    float _w, _h;
    float _speed;
    float _health,
          _mhealth;
    float _damage;
    bool  _dead;
    bool _hit;
            

    Texture _tex;

    void _init(float x = 0, float y = 0);
};

#endif