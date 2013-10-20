#include "engine.h"

void Engine::init(Window *window, void (*_init)(Engine*), void (*logic)(Engine*), void (*render)(Engine*), void (*free)(Engine*), const char* name) {
	_window = window;
	_logic  = logic;
	_render = render;
	_free   = free;

	if(_init != nullptr) _init(this);

	_name = name;
}

void Engine::exec(void) {
	_window->clear();

	if(_logic != nullptr) _logic(this);
	if(_render != nullptr) _render(this);

	_window->render();

	_window->incFrames();
}
