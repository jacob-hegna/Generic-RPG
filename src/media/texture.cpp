#include "texture.h"

void Texture::init(SDL_Renderer *ren) {
	_ren = ren;
}

void Texture::loadIMG(std::string path) {
	free();

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == nullptr )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );
        _tex = SDL_CreateTextureFromSurface( _ren, loadedSurface );
		if( _tex == nullptr )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
			_w = loadedSurface->w;
			_h = loadedSurface->h;

		SDL_FreeSurface( loadedSurface );
	}
}

void Texture::render(int x, int y) {
	SDL_Rect temp;
	temp.x = x;
	temp.y = y;
	SDL_QueryTexture(_tex, NULL, NULL, &temp.w, &temp.h);
	SDL_RenderCopy(_ren, _tex, NULL, &temp);
}

void Texture::free(void) {
	if(!_free && _tex != nullptr) {
		_free = true;
		SDL_DestroyTexture(_tex);
		_tex = nullptr;
	}
}