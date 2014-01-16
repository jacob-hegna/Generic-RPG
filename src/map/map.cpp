#include "map.h"

void Map::init(std::string path) {
	Texture input;
	input.loadIMG("media/images/etc/map.bmp");
	_w = input.getW();
	_h = input.getH();
	_tex = new Texture*[_w];
	for(int i = 0; i < _w; ++i) {
		_tex[i] = new Texture[_h]; 
	}


}

void Map::free(void) {
	for(int i = 0; i < _w; ++i) {
		for(int j = 0; j < _h; ++j) {
			_tex[i][j].free();
		}
	}
}	