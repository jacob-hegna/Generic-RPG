#ifndef _BUFFUNC_H_
#define _BUFFUNC_H_

template<class Func, class P1, class P2>
void bufFunc(bool condition, bool *buf, Func func, P1 p1, P2 p2) {
    if(condition) {
            if(!*buf) {
                func(p1, p2);
                *buf = true;
            }
        } else {
            *buf = false;
        }
}

#endif