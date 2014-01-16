#include "window.h"

#include <cstring>

Window::~Window(void) {
	free();
}

void Window::free(void) {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	delete _event;
	delete _window;
	delete _renderer;
}

int Window::init(void)
{
	_clearColor.r = 0xFF;
	_clearColor.g = 0xFF;
	_clearColor.b = 0xFF;
	_x = 100;
	_y = 100;
	_w = 800;
	_h = 600;
	_title = "Divide and Conquer";
	_aa = 16;
	_fc = false;
	_time    = 0;
	_frames  = 0;
	_close   = false;

	SDL_SetHint( SDL_HINT_RENDER_VSYNC, "1" );
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	_window = SDL_CreateWindow( _title.c_str(), _x, _y, _w, _h, SDL_WINDOW_SHOWN );
	_event  = new SDL_Event;

	_renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(_renderer, _clearColor.r, _clearColor.g, _clearColor.b, 0xFF);

	SDL_SetWindowIcon(_window, IMG_Load("media/images/etc/icon.bmp"));

	return 0;
}
