#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <iostream>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include <SDL.h>

class Window
{
public:
	Window(void) {
		// Nothing to do here...
	}

	~Window(void);

	void free(void);

	static int initSDL(void) {
		if(!SDL_Init(SDL_INIT_EVERYTHING)) {
			return -1;
		}
		return 0;
	}

	static void deinitSDL(void) {
		SDL_Quit();
	}

	int init(void);

	void update(void) {
		SDL_PollEvent(_event);
	}

	void render(void) {
		SDL_UpdateWindowSurface(_window);
	}

	void clear(void);

	SDL_Event* getEvent(void) {
		return _event;
	}

	SDL_Window* getWindow(void) {
		return _window;
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
	void setW(int w) {
		_w = w;
	}

	int getH(void) {
		return _h;
	}
	void setH(int h) {
		_h = h;
	}

	void incFrames(void) {
		++_frames;
	}

private:
	SDL_Window  *_window;
	SDL_Event   *_event;
	SDL_Surface *_clear;

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
