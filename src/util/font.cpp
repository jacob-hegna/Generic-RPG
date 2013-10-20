#include "font.h"

void Font::loadTTF(std::string path, int size) {
	_font = TTF_OpenFont(path.c_str(), size);
}

void Font::setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
	_color.r = r;
	_color.g = g;
	_color.b = b;
	_color.a = a;
	
}

void Font::print(std::string data, int x, int y) {
	if(_tex != nullptr) SDL_DestroyTexture(_tex);
	
	SDL_Surface* textSurface = TTF_RenderText_Solid( _font, data.c_str(), _color );
	if( textSurface == nullptr )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
        _tex = SDL_CreateTextureFromSurface( _ren, textSurface );
		if( _tex == nullptr )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			_w = textSurface->w;
			_h = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	temp.w = _w;
	temp.h = _h;
	SDL_RenderCopy(_ren, _tex, NULL, &temp);
}

void Font::free(void) {
	SDL_DestroyTexture(_tex);
	TTF_CloseFont(_font);
}