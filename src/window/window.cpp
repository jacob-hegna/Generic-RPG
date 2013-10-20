#include "window.h"

#include <cstring>

using namespace rapidxml;

Window::~Window(void) {
	free();
}

void Window::free(void) {
	SDL_DestroyWindow(_window);
	SDL_FreeSurface(_clear);
	delete _event;
	delete _window;
	delete _clear;
}

int Window::init(void)
{
	// Input
	struct stat buffer;
	if(stat("settings.xml", &buffer) == 0) {
		file<> xmlFile("settings.xml");
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<> *root = doc.first_node("window");

		xml_attribute<> *rootAddr = root->first_attribute("title");
		_title = rootAddr->value();
		rootAddr = rootAddr->next_attribute("aa");
		_aa = atof(rootAddr->value());


		xml_node<> *node = root->first_node("pos");
		xml_attribute<> *attr = node->first_attribute("x");
		_x = atoi(attr->value());
		attr = attr->next_attribute("y");
		_y = atoi(attr->value());

		node = node->next_sibling("size");
		attr = node->first_attribute("w");
		_w = atoi(attr->value());
		attr = attr->next_attribute("h");
		_h = atoi(attr->value());
		attr = attr->next_attribute("fullscreen");
		_fc = (atoi(attr->value()) == 1) ? true : false;

		node = node->next_sibling("color");
		attr = node->first_attribute("r");
		_clearColor.r = atoi(attr->value());
		attr = attr->next_attribute("g");
		_clearColor.g = atoi(attr->value());
		attr = attr->next_attribute("b");
		_clearColor.b = atoi(attr->value());
	} else {
		std::ofstream ofile("settings.xml");
		ofile << "<window title=\"Generic-RPG\" aa=\"16\">"                                                    << std::endl
			  << "  <pos  x=\"15\" y=\"15\"/>"                                                                 << std::endl
			  << "  <size w=\"800\" h=\"600\" fullscreen=\"0\"/>"                                              << std::endl
			  << "  <color r=\"255\" g=\"255\" b=\"255\"/>"                                                 << std::endl
		      << "</window>"                                                                                   << std::endl;
		ofile.close();
		_clearColor.r = 0xFF;
		_clearColor.g = 0xFF;
		_clearColor.b = 0xFF;
		_x = 50;
		_y = 50;
		_w = 800;
		_h = 600;
		_title = "Divide and Conquer";
		_aa = 16;
		_fc = false;
	}
	_time    = 0;
	_frames  = 0;
	_close   = false;

	_window = SDL_CreateWindow( _title.c_str(), _x, _y, _w, _h, SDL_WINDOW_SHOWN );
	_event  = new SDL_Event;

	return 0;
}

void Window::clear(void) {
	_clear = SDL_GetWindowSurface(_window);
	SDL_FillRect(_clear, NULL, SDL_MapRGB(_clear->format, _clearColor.r, _clearColor.g, _clearColor.b));
}
