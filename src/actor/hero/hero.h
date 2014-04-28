#ifndef _HERO_H_
#define _HERO_H_

#include "../actor.h"
#include "../../media/mixer/sound.h"
#include "../../util/buffunc.h"
#include "../../states/gameplay/map.h"
#include "../../util/timer.h"

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
    void move(Gameplay::Map *map);

    void shiftX(float dx) {_x+=dx;}
    bool ifAttack(void) {
        return (_pos==SFRONT||_pos==SBACK||_pos==SLEFT||_pos==SRIGHT);
    }

    void  renderMagic(void);
    bool  isMagicAttack(void) {return _magicAttack;}

    float getMagic(void)  {return _magic;}
    float getMMagic(void) {return _mMagic;}

private:
    void _free(void);

    float _magic;
    float _mMagic;

    Texture _multiTex[8];
    Texture _magicTex;
    bool    _magicAttack;
    Sound   _slashSound;
    bool    _slash;
    bool    _playBuf;
    bool    _shiftBuf;

    enum {
        NFRONT, NBACK, NLEFT, NRIGHT,
        SFRONT, SBACK, SLEFT, SRIGHT
    } _pos;
};

#endif