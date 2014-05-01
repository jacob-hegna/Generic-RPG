#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <cmath>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

class Window
{
public:
    Window(void) {
        // Nothing to do here...
    }

    ~Window(void);

    void free(void);

    static int initSDL(void) {
        if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
            return -1;
        }
        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        return 0;
    }

    static void deinitSDL(void) {
        Mix_Quit();
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    int init(void);

    void update(void) {
        SDL_PollEvent(_event);
    }

    void render(void) {
        SDL_RenderPresent(_renderer);
    }

    void clear(void) {
        SDL_RenderClear(_renderer);
    }

    SDL_Event* getEvent(void) {
        return _event;
    }

    SDL_Window* getWindow(void) {
        return _window;
    }

    SDL_Renderer* getRen(void) {
        return _renderer;
    }

    bool shouldClose(void) {
        return _close;
    }

    void close(void) {
        _close = true;
    }

    int getX(void) {
        return _x;
    }

    int getY(void) {
        return _y;
    }

    int getW(void) {
        return _w;
    }

    int getH(void) {
        return _h;
    }

    void incFrames(void) {
        ++_frames;
    }
    int getFrames(void) {
        return _frames;
    }

private:
    SDL_Window   *_window;
    SDL_Event    *_event;
    SDL_Renderer *_renderer;

    bool _close;

    std::string _title;
    int _x, _y;
    int _w, _h;
    bool _fc;
    int _aa;

    int  _frames;
    float _time,
         _stime;

    struct
    {
        Uint8 r, g, b;
    } _clearColor;
};

#endif
