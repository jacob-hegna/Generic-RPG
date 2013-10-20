#include "window.h"

#include <cstring>

using namespace rapidxml;

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
			  << "  <pos  x=\"100\" y=\"100\"/>"                                                               << std::endl
			  << "  <size w=\"800\" h=\"600\" fullscreen=\"0\"/>"                                              << std::endl
			  << "  <color r=\"255\" g=\"255\" b=\"255\"/>"                                                    << std::endl
		      << "</window>"                                                                                   << std::endl;
		ofile.close();
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
	}
	_time    = 0;
	_frames  = 0;
	_close   = false;

	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	_window = SDL_CreateWindow( _title.c_str(), _x, _y, _w, _h, SDL_WINDOW_SHOWN );
	_event  = new SDL_Event;

	_renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
	SDL_SetRenderDrawColor(_renderer, _clearColor.r, _clearColor.g, _clearColor.b, 0xFF);

	return 0;
}

SDL_Texture* Window::loadTex(std::string path) {
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        newTexture = SDL_CreateTextureFromSurface( _renderer, loadedSurface );
		if( newTexture == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void Window::applyTex(SDL_Texture *tex, int x, int y) {
	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	SDL_QueryTexture(tex, NULL, NULL, &temp.w, &temp.h);
	SDL_RenderCopy(_renderer, tex, NULL, &temp);
}